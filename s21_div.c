#include "s21_div.h"

#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = OK;
  char tmp_code = 0;
  int sign_value_1 = get_bit(value_1, 3, 31);
  int sign_value_2 = get_bit(value_2, 3, 31);
  int sign_result = 0;
  unsigned int result_scale = 0;

  if DECIMAL_IS_ZERO (value_2) {
    error_code = DIV_BY_ZERO;
  } else {
    if (sign_value_1 != sign_value_2) {
      sign_result = 1;
    }
    num_as_bytes dividend, divisor, quotient;
    scale_before_div(value_1, value_2, &dividend, &divisor);
    result_scale = num_as_bytes_division_dec_fractions(dividend, divisor,
                                                       &quotient, &tmp_code);
    if (tmp_code != 1) {
      for (int i = 0; i < 4; i++) {
        result->bits[i] = 0;
      }
      num_as_bytes_to_s21_decimal(sign_result, result_scale, quotient, result);
    } else {
      error_code = sign_result == 1 ? INF_MINUS : INF_PLUS;
    }
    num_as_bytes_free(&divisor);
    num_as_bytes_free(&dividend);
    num_as_bytes_free(&quotient);
  }
  return error_code;
}