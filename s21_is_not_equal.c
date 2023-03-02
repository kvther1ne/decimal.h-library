#include "s21_decimal.h"

int s21_is_not_equal(s21_decimal x, s21_decimal y) {
  int negative_a = get_bit(x, 3, 31);
  int negative_b = get_bit(y, 3, 31);
  if ((negative_a != negative_b) && (!ZERO_DECIMAL_A && !ZERO_DECIMAL_B)) {
    return 1;
  } else {
    big_decimal big_a = {0};
    big_decimal big_b = {0};
    int scale_a = 0;
    int scale_b = 0;
    help_in_scaling_values(x, y, &big_a, &big_b, &scale_a, &scale_b);
    int temp = 0, left, right;
    for (int i = 5; i >= 0; i--) {
      for (int k = 31; k >= 0; k--) {
        if (temp == 0) {
          left = get_bit_big(big_a, i, k), right = get_bit_big(big_b, i, k);
          if (left != right) {
            temp = 1;
          }
        }
      }
    }
    return temp;
  }
}