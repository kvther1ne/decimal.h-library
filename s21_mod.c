#include "s21_decimal.h"
#include "s21_div.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error_code = OK;
  int sign_value_1 = get_bit(value_1, 3, 31);
  int sign_value_2 = get_bit(value_2, 3, 31);
  int sign_result = 0;
  unsigned int result_scale = get_result_scale_mod(value_1, value_2);

  if DECIMAL_IS_ZERO (value_2) {
    error_code = DIV_BY_ZERO;
  } else {
    if (sign_value_1 == 1 || sign_value_2 == 1) {
      sign_result = 1;
    }
    num_as_bytes dividend, divisor, quotient, remainder;
    scale_before_div(value_1, value_2, &dividend, &divisor);
    get_quotient_and_remainder(dividend, divisor, &quotient, &remainder);
    for (int i = 0; i < 4; i++) {
      result->bits[i] = 0;
    }
    num_as_bytes_to_s21_decimal(sign_result, result_scale, remainder, result);
    num_as_bytes_free(&divisor);
    num_as_bytes_free(&dividend);
    num_as_bytes_free(&quotient);
    num_as_bytes_free(&remainder);
  }
  return error_code;
}