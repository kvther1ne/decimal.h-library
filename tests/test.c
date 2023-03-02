#include "test.h"

#include "math.h"

int main() {
  int no_failed = 0;
  SRunner* runner;

  // Forming a "runner" to test different cases
  runner = srunner_create(test_from_int_to_decimal());
  srunner_add_suite(runner, test_from_float_to_decimal());
  srunner_add_suite(runner, test_from_decimal_to_int());
  srunner_add_suite(runner, test_from_decimal_to_float());
  srunner_add_suite(runner, test_multiply());
  srunner_add_suite(runner, test_round());
  srunner_add_suite(runner, test_sub());
  srunner_add_suite(runner, test_greater());
  srunner_add_suite(runner, test_equal());
  srunner_add_suite(runner, test_less_or_equal());
  srunner_add_suite(runner, test_greater_or_equal());
  srunner_add_suite(runner, test_less());
  srunner_add_suite(runner, test_not_equal());
  srunner_add_suite(runner, test_add());
  srunner_add_suite(runner, test_div());
  srunner_add_suite(runner, test_mod());

  // Running and counting failed test cases
  srunner_run_all(runner, CK_ENV);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void create_decimal_from_arr(s21_decimal* dec, unsigned int sign,
                             unsigned int scale, unsigned int high,
                             unsigned int mid, unsigned int low) {
  dec->bits[0] = low;
  dec->bits[1] = mid;
  dec->bits[2] = high;
  dec->bits[3] = (sign << 31) + (scale << 16);
}