#include "s21_decimal.h"

int compression_big_dec_to_dec(big_decimal* buffer, unsigned int* last_rem,
                               unsigned int* rem);

int s21_negate(s21_decimal value, s21_decimal* result) {
  int status;
  status = OK;
  if (result != NULL) {
    for (int i = 0; i < 4; i++) {
      result->bits[i] = value.bits[i];
    }
    result->bits[3] ^= 1 << 31;
  } else {
    status = 1;
  }
  return status;
}

int s21_floor(s21_decimal value, s21_decimal* result) {
  unsigned int last_rem, rem, sign;
  int scale, status;
  big_decimal temp_buf;

  status = OK;
  last_rem = 0, rem = 0;
  sign = (value.bits[3] & MASK_SIGN) >> 31;
  scale = (value.bits[3] & MASK_SCALE) >> 16;

  if (result == NULL || scale > 28) {
    status = ERROR_ROUND;
  } else {
    decimal_to_big_decimal(value, &temp_buf);
    div10_big_decimal(&temp_buf, scale, &rem, &last_rem);
    rem |= last_rem;

    if (sign && (rem > 0)) {
      add_uint(&temp_buf, 1U);
    }
    big_decimal_to_decimal(temp_buf, sign, 0, result);
  }
  return status;
}

int s21_round(s21_decimal value, s21_decimal* result) {
  unsigned int sign, last_rem, rem;
  int scale, status;
  big_decimal temp_buf;

  status = OK;
  rem = 0, last_rem = 0;
  scale = (value.bits[3] & MASK_SCALE) >> 16;
  sign = (value.bits[3] & MASK_SIGN) >> 31;

  if (result == NULL || scale > 28) {
    status = ERROR_ROUND;
  } else if (scale > 0) {
    decimal_to_big_decimal(value, &temp_buf);
    div10_big_decimal(&temp_buf, scale - 1, &rem, &last_rem);

    // get the last remainder of division by 10
    rem |= last_rem;
    div10_big_decimal(&temp_buf, 1, &rem, &last_rem);

    if (((rem > 0U || (temp_buf.part[0] & 1U)) && (last_rem == 5U)) ||
        (last_rem > 5U)) {
      add_uint(&temp_buf, 1U);
    }
    big_decimal_to_decimal(temp_buf, sign, 0, result);
  } else {
    for (int i = 0; i < 4; i++) {
      result->bits[i] = value.bits[i];
    }
  }
  return status;
}

int s21_truncate(s21_decimal value, s21_decimal* result) {
  unsigned int sign, rem, last_rem;
  int scale, status;
  big_decimal temp_buf;

  status = OK;
  scale = (value.bits[3] & MASK_SCALE) >> 16;
  sign = (value.bits[3] & MASK_SIGN) >> 31;

  if (result == NULL || scale > 28) {
    status = ERROR_ROUND;
  } else {
    decimal_to_big_decimal(value, &temp_buf);
    div10_big_decimal(&temp_buf, scale, &rem, &last_rem);
    big_decimal_to_decimal(temp_buf, sign, 0, result);
  }
  return status;
}

void bank_round(big_decimal* buffer, unsigned int* round_scale) {
  unsigned int last_rem, rem, div_scale;
  last_rem = 0, rem = 0, div_scale = 0;

  div_scale = compression_big_dec_to_dec(buffer, &last_rem, &rem);
  // banking condition
  if (((rem > 0U || (buffer->part[0] & 1U)) && (last_rem == 5U)) ||
      (last_rem > 5U)) {
    add_uint(buffer, 1U);
    div_scale += compression_big_dec_to_dec(buffer, &last_rem, &rem);
  }
  *round_scale = div_scale;
}

int compression_big_dec_to_dec(big_decimal* buffer, unsigned int* last_rem,
                               unsigned int* rem) {
  unsigned int divider, div_scale;
  *last_rem = 0, *rem = 0;
  div_scale = 0;
  while ((buffer->part[5] | buffer->part[4] | buffer->part[3]) > 0) {
    *rem |= *last_rem;
    if ((buffer->part[3] > 999999999U) ||
        ((buffer->part[5] | buffer->part[4]) != 0U)) {
      divider = 1000000000U;
      div_scale += 9;
    } else if (buffer->part[3] > 9999U) {
      divider = 1000U;
      div_scale += 3;
    } else {
      divider = 10U;
      div_scale += 1;
    }
    div_big_decimal_on_uint(buffer, divider, last_rem);
  }
  return div_scale;
}