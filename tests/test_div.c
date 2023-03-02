#include "test.h"

START_TEST(test_s21_div) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 12432536
  create_decimal_from_arr(&a, 0U, 0U, 0U, 0U, 12432536U);
  // 3635
  create_decimal_from_arr(&b, 0U, 0U, 0U, 0U, 3635U);
  // 3420.2299862448418156808803301
  create_decimal_from_arr(&ans, 0U, 25U, 1854110390U, 3192716432U, 2500105189U);

  status = s21_div(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_same) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 1124235436
  create_decimal_from_arr(&a, 0U, 0U, 0U, 0U, 1124235436U);
  // 1124235436
  create_decimal_from_arr(&b, 0U, 0U, 0U, 0U, 1124235436U);
  // 1
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 1U);

  status = s21_div(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_max_decimal_by_two) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 79228162514264337593543950335
  create_decimal_from_arr(&a, 0U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // 2
  create_decimal_from_arr(&b, 0U, 0U, 0U, 0U, 2U);
  // 39614081257132168796771975168
  create_decimal_from_arr(&ans, 0U, 0U, 2147483648U, 0U, 0U);

  status = s21_div(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_close_to_one) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 79228162514264337593543950335
  create_decimal_from_arr(&a, 0U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // 1.000000000000000000000000001
  create_decimal_from_arr(&b, 0U, 27U, 54210108U, 2681241660U, 3892314113U);
  // 79228162514264337593543950256
  create_decimal_from_arr(&ans, 0U, 0U, 4294967295U, 4294967295U, 4294967216U);

  status = s21_div(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_by_one) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 79228162514264337593543950335
  create_decimal_from_arr(&a, 0U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // 1
  create_decimal_from_arr(&b, 0U, 0U, 0U, 0U, 1U);
  // 79228162514264337593543950335
  create_decimal_from_arr(&ans, 0U, 0U, 4294967295U, 4294967295U, 4294967295U);

  status = s21_div(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_big_numbers) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 79228162514264337593543950335
  create_decimal_from_arr(&a, 0U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // 79228162514264123143423534531
  create_decimal_from_arr(&b, 0U, 0U, 4294967295U, 4294917365U, 1891640771U);
  // 1.0000000000000027067410578555
  create_decimal_from_arr(&ans, 0U, 28U, 542101086U, 1042619135U, 795114619U);

  status = s21_div(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_period) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 5
  create_decimal_from_arr(&a, 0U, 0U, 0U, 0U, 5U);
  // 3
  create_decimal_from_arr(&b, 0U, 0U, 0U, 0U, 3U);
  // 1.6666666666666666666666666667
  create_decimal_from_arr(&ans, 0U, 28U, 903501810U, 1737688055U, 447392427U);

  status = s21_div(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_divisor_lower_one) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 12115.25
  create_decimal_from_arr(&a, 0U, 2U, 0U, 0U, 1211525U);
  // 0.012
  create_decimal_from_arr(&b, 0U, 3U, 0U, 0U, 12U);
  // 1009604.1666666666666666666667
  create_decimal_from_arr(&ans, 0U, 22U, 547307515U, 1826257244U, 2886380203U);

  status = s21_div(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_smaller_dividend) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 2
  create_decimal_from_arr(&a, 0U, 0U, 0U, 0U, 2U);
  // 5
  create_decimal_from_arr(&b, 0U, 0U, 0U, 0U, 5U);
  // 0.4
  create_decimal_from_arr(&ans, 0U, 1U, 0U, 0U, 4U);

  status = s21_div(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_dividend_is_zero) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 0
  create_decimal_from_arr(&a, 0U, 0U, 0U, 0U, 0U);
  // 2332
  create_decimal_from_arr(&b, 0U, 0U, 0U, 0U, 2332U);
  // 0
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 0U);

  status = s21_div(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_divident_negative) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // -2231
  create_decimal_from_arr(&a, 1U, 0U, 0U, 0U, 2231U);
  // 23
  create_decimal_from_arr(&b, 0U, 0U, 0U, 0U, 23U);
  // -97
  create_decimal_from_arr(&ans, 1U, 0U, 0U, 0U, 97U);

  status = s21_div(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_divisor_negative) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 12423
  create_decimal_from_arr(&a, 0U, 0U, 0U, 0U, 12423U);
  // -23
  create_decimal_from_arr(&b, 1U, 0U, 0U, 0U, 23U);
  // -540.13043478260869565217391304
  create_decimal_from_arr(&ans, 1U, 26U, 2928052954U, 361731093U, 3591783112U);

  status = s21_div(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_both_negative) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // -124123
  create_decimal_from_arr(&a, 1U, 0U, 0U, 0U, 124123U);
  // -425
  create_decimal_from_arr(&b, 1U, 0U, 0U, 0U, 425U);
  // 292.05411764705882352941176470
  create_decimal_from_arr(&ans, 0U, 26U, 1583228544U, 779070022U, 3264648854U);

  status = s21_div(a, b, &res_dec);
  // print_decimal(res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_divisor_is_zero) {
  int status;
  s21_decimal a, b, res_dec;
  // 124123
  create_decimal_from_arr(&a, 0U, 0U, 0U, 0U, 124123U);
  // 0
  create_decimal_from_arr(&b, 0U, 0U, 0U, 0U, 0U);

  status = s21_div(a, b, &res_dec);
  ck_assert((status == DIV_BY_ZERO));
}
END_TEST

START_TEST(test_inf_plus) {
  int status;
  s21_decimal a, b, res_dec;
  // 79228162514264337593543950335
  create_decimal_from_arr(&a, 0U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // 0.5
  create_decimal_from_arr(&b, 0U, 1U, 0U, 0U, 5U);

  status = s21_div(a, b, &res_dec);
  ck_assert((status == INF_PLUS));
}
END_TEST

START_TEST(test_inf_minus) {
  int status;
  s21_decimal a, b, res_dec;
  // -79228162514264337593543950335
  create_decimal_from_arr(&a, 1U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // 0.5
  create_decimal_from_arr(&b, 0U, 1U, 0U, 0U, 5U);

  status = s21_div(a, b, &res_dec);
  ck_assert((status == INF_MINUS));
}
END_TEST

START_TEST(test_two_lower_one) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 0.00000102412
  create_decimal_from_arr(&a, 0U, 11U, 0U, 0U, 102412U);
  // 9.999135E-8
  create_decimal_from_arr(&b, 0U, 14U, 0U, 0U, 9999135U);
  // 10.242085940433847527811155665
  create_decimal_from_arr(&ans, 0U, 27U, 555224591U, 1589485415U, 4130178769U);

  status = s21_div(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

Suite *test_div() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Div");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_div);
  tcase_add_test(tc_core, test_same);
  tcase_add_test(tc_core, test_max_decimal_by_two);
  tcase_add_test(tc_core, test_close_to_one);
  tcase_add_test(tc_core, test_by_one);
  tcase_add_test(tc_core, test_big_numbers);
  tcase_add_test(tc_core, test_period);
  tcase_add_test(tc_core, test_divisor_lower_one);
  tcase_add_test(tc_core, test_smaller_dividend);
  tcase_add_test(tc_core, test_dividend_is_zero);
  tcase_add_test(tc_core, test_divident_negative);
  tcase_add_test(tc_core, test_divisor_negative);
  tcase_add_test(tc_core, test_both_negative);
  tcase_add_test(tc_core, test_divisor_is_zero);
  tcase_add_test(tc_core, test_inf_minus);
  tcase_add_test(tc_core, test_inf_plus);
  tcase_add_test(tc_core, test_two_lower_one);

  suite_add_tcase(s, tc_core);

  return s;
}