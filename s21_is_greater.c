#include "s21_decimal.h"

int s21_is_greater(s21_decimal x, s21_decimal y) {
  int negative_a = get_bit(x, 3, 31);
  int negative_b = get_bit(y, 3, 31);
  if ((negative_a > negative_b) || (ZERO_DECIMAL_A && ZERO_DECIMAL_B)) return 0;
  if (negative_a < negative_b) return 1;
  int flag = (negative_a == 1 && negative_b == 1) ? 1 : 0;
  //========Если знаки децималов не отличаются========
  big_decimal big_a = {0};
  big_decimal big_b = {0};
  int scale_a = 0;
  int scale_b = 0;
  help_in_scaling_values(x, y, &big_a, &big_b, &scale_a, &scale_b);
  int result = comparison(big_a, big_b, flag);
  return result == 1 ? 1 : 0;
}