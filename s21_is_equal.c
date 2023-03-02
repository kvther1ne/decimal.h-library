#include "s21_decimal.h"

int s21_is_equal(s21_decimal x, s21_decimal y) {
  int negative_a = get_bit(x, 3, 31);
  int negative_b = get_bit(y, 3, 31);
  if ((negative_a != negative_b) && (!ZERO_DECIMAL_A && !ZERO_DECIMAL_B)) {
    return 0;
  } else {
    big_decimal big_a = {0};
    big_decimal big_b = {0};
    int scale_a = 0;
    int scale_b = 0;
    help_in_scaling_values(x, y, &big_a, &big_b, &scale_a, &scale_b);
    int flag = (negative_a == 1 && negative_b == 1) ? 1 : 0;
    int res = comparison(big_a, big_b, flag);
    return res == 0 ? 1 : 0;
  }
}