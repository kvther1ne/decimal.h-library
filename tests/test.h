#ifndef _TESTS_
#define _TESTS_

#include <check.h>

#include "../s21_decimal.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// Test Case Packages
Suite *test_from_int_to_decimal();
Suite *test_from_float_to_decimal();
Suite *test_from_decimal_to_int();
Suite *test_from_decimal_to_float();
Suite *test_multiply();
Suite *test_round();
Suite *test_sub();
Suite *test_greater();
Suite *test_less_or_equal();
Suite *test_equal();
Suite *test_greater_or_equal();
Suite *test_less();
Suite *test_not_equal();
Suite *test_add();
Suite *test_div();
Suite *test_mod();

void create_decimal_from_arr(s21_decimal *dec, unsigned int sign,
                             unsigned int scale, unsigned int high,
                             unsigned int mid, unsigned int low);

// int main();
#endif  // _TESTS_