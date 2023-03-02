#include "s21_decimal.h"

void _mul_base_part(unsigned long *temp, unsigned long *temp2,
                    s21_decimal value_1, s21_decimal value_2,
                    big_decimal *big_result) {
  // low, low
  *temp = mul_32x32_to_64(value_1.bits[0], value_2.bits[0]);
  big_result->part[0] = (unsigned int)*temp;
  //=======================================================================
  // low, mid
  *temp2 = mul_32x32_to_64(value_1.bits[0], value_2.bits[1]) + (*temp >> 32);
  // mid, low
  *temp = mul_32x32_to_64(value_1.bits[1], value_2.bits[0]);
  *temp += *temp2;  // Может быть переполнение
  big_result->part[1] = (unsigned int)*temp;
  //=======================================================================
  if (*temp < *temp2) {  // Проверка на переполнение
    *temp2 = (*temp >> 32) | (1UL << 32);  // Добавили 1 из "65 бита"
  } else {
    *temp2 = *temp >> 32;
  }

  // Mid, mid
  *temp = mul_32x32_to_64(value_1.bits[1], value_2.bits[1]);
  *temp += *temp2;
}

void _mul_high_part(unsigned long temp, unsigned long temp2,
                    s21_decimal value_1, s21_decimal value_2,
                    big_decimal *big_result) {
  unsigned long int temp3;
  // Low, high
  temp2 = mul_32x32_to_64(value_1.bits[0], value_2.bits[2]);
  temp += temp2;
  temp3 = 0;
  if (temp < temp2) {
    temp3 += 1;
  }

  // High, low
  temp2 = mul_32x32_to_64(value_1.bits[2], value_2.bits[0]);
  temp += temp2;
  big_result->part[2] = (unsigned int)temp;
  //=======================================================================
  if (temp < temp2) {
    temp3 += 1;
  }
  temp2 = (temp3 << 32) | (temp >> 32);

  // Mid, high
  temp = mul_32x32_to_64(value_1.bits[1], value_2.bits[2]);
  temp += temp2;
  temp3 = 0;
  if (temp < temp2) {
    temp3 += 1;
  }

  // High, mid
  temp2 = mul_32x32_to_64(value_1.bits[2], value_2.bits[1]);
  temp += temp2;
  big_result->part[3] = (unsigned int)temp;

  //=======================================================================
  if (temp < temp2) {
    temp3 += 1;
  }
  temp = (temp3 << 32) | (temp >> 32);

  // High, high
  temp2 = mul_32x32_to_64(value_1.bits[2], value_2.bits[2]);
  temp += temp2;  // Переполнение исключено
  big_result->part[4] = (unsigned int)temp;
  big_result->part[5] = (unsigned int)(temp >> 32);
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  unsigned int status = OK;
  unsigned long int temp, temp2;
  big_decimal big_result;
  for (size_t i = 0; i < 6; i++) {
    big_result.part[i] = 0;
  }

  _mul_base_part(&temp, &temp2, value_1, value_2, &big_result);
  if ((value_1.bits[2] | value_2.bits[2]) > 0) {
    _mul_high_part(temp, temp2, value_1, value_2, &big_result);
  } else {
    big_result.part[2] = (unsigned int)temp;
    big_result.part[3] = (unsigned int)(temp >> 32);
  }
  unsigned int round_scale = 0;
  bank_round(&big_result, &round_scale);

  unsigned int res_scale = 0, res_sign = 0, original_scale;
  original_scale = ((value_1.bits[3] + value_2.bits[3]) & MASK_SCALE) >> 16;
  res_scale = original_scale - round_scale;
  res_sign = (value_1.bits[3] ^ value_2.bits[3]) >> 31;

  if (res_scale > 28) {
    if (res_sign) {
      status = INF_MINUS;
    } else {
      status = INF_PLUS;
    }
  } else {
    big_decimal_to_decimal(big_result, res_sign, res_scale, result);
  }
  return status;
}
