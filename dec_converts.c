#include "s21_decimal.h"

void core_f2d(int exponent, const double dbl_pow10[50], double dbl_src,
              s21_decimal *dst);

void reset_value(s21_decimal *num) {
  for (int i = 0; i < 4; i++) {
    num->bits[i] = 0;
  }
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int status = CONVERSION_ERROR;
  if (NULL != dst) {
    dst->bits[3] = src & (1 << 31);
    if (src < 0) {
      src = -src;
    }
    dst->bits[0] = src;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    status = OK;
  }
  return status;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int status, exponent;
  double dbl_src = src;
  const double dbl_pow10[50] = {
      1,    1e1,  1e2,  1e3,  1e4,  1e5,  1e6,  1e7,  1e8,  1e9,
      1e10, 1e11, 1e12, 1e13, 1e14, 1e15, 1e16, 1e17, 1e18, 1e19,
      1e20, 1e21, 1e22, 1e23, 1e24, 1e25, 1e26, 1e27, 1e28, 1e29,
      1e30, 1e31, 1e32, 1e33, 1e34, 1e35, 1e36, 1e37, 1e38, 1e39,
      1e40, 1e41, 1e42, 1e43, 1e44, 1e45, 1e46, 1e47, 1e48, 1e49};
  exponent = ((*((unsigned int *)&src) & 0x7F800000) >> 23) - 126;
  status = OK;
  if (exponent < -94) {
    reset_value(dst);

    if (*((unsigned int *)&src) != 0) {
      status = CONVERSION_ERROR;
    }
    reset_value(dst);
  } else if (exponent > 96) {
    status = CONVERSION_ERROR;
  } else {
    core_f2d(exponent, dbl_pow10, dbl_src, dst);
  }
  return status;
}

// calculating the necessary power for
// the decimals in 10^(power) from 2^(exp)
// log_10(2) * 2 ^ 16 = 19728.3
// ((exponent * 19728) >> 16 ==
// exp * (log_10(2) * 2 ^ 16) / 2^16
// without use lib "math.h"
void core_f2d(int exponent, const double dbl_pow10[50], double dbl_src,
              s21_decimal *dst) {
  int power;
  unsigned int main_part, sign;
  power = 6 - ((exponent * 19728) >> 16);
  if (dbl_src < 0) {
    dbl_src = -dbl_src;
    sign = 1;
  } else {
    sign = 0;
  }
  if (power >= 0) {
    if (power > DEC_MAX_SCALE) {
      power = DEC_MAX_SCALE;
    }
    dbl_src *= dbl_pow10[power];
  } else {
    if (dbl_src >= 1e7 || power != -1) {
      dbl_src /= dbl_pow10[-power];
    } else {
      power = 0;
    }
  }
  if (dbl_src < 1e6 && power < DEC_MAX_SCALE) {
    dbl_src *= 10;
    power += 1;
  }
  main_part = (unsigned int)((int)dbl_src);
  dbl_src -= (int)main_part;
  if (dbl_src > 0.5 || (dbl_src == 0.5 && (main_part & 1) != 0)) {
    main_part += 1;
  }
  big_decimal temp_buf = {0}, res = {0};
  unsigned int rem, last_rem;
  res.part[0] = main_part;
  if (power < 0) {
    power = -power;
    mul10xbig_decimal(&res, power);
    power = 0;
  } else {
    for (int i = 3; i >= 0; i--) {
      temp_buf = res;
      div10_big_decimal(&temp_buf, i, &rem, &last_rem);
      if (last_rem == 0 && power >= i) {
        res = temp_buf;
        power -= i;
      }
    }
  }
  big_decimal_to_decimal(res, sign, power, dst);
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int status;
  status = OK;
  s21_decimal temp;
  s21_truncate(src, &temp);
  if ((temp.bits[2] | temp.bits[1] | (temp.bits[0] & MASK_SIGN)) > 0 ||
      dst == NULL) {
    status = CONVERSION_ERROR;
  } else {
    *dst = ((temp.bits[3] & MASK_SIGN) > 0) ? -(temp.bits[0]) : temp.bits[0];
  }
  return status;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int status;
  const double dbl_pow10[] = {1,    1e1,  1e2,  1e3,  1e4,  1e5,  1e6,  1e7,
                              1e8,  1e9,  1e10, 1e11, 1e12, 1e13, 1e14, 1e15,
                              1e16, 1e17, 1e18, 1e19, 1e20, 1e21, 1e22, 1e23,
                              1e24, 1e25, 1e26, 1e27, 1e28, 1e29};
  double q2, q1, res_dbl;
  q2 = 1.8446744073709552e19;
  q1 = 4294967296.;
  status = OK;

  if (NULL == dst) {
    status = CONVERSION_ERROR;
  } else {
    res_dbl = (q2 * (double)src.bits[2] + q1 * (double)src.bits[1] +
               (double)src.bits[0]) /
              dbl_pow10[(src.bits[3] & MASK_SCALE) >> 16];

    if (((src.bits[3] & MASK_SIGN) >> 31) > 0) {
      res_dbl = -res_dbl;
    }
    *dst = (float)res_dbl;
  }
  return status;
}