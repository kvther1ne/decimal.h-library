#include "test.h"

START_TEST(test_s21_mod) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 534.5468
  create_decimal_from_arr(&a, 0U, 4U, 0U, 0U, 5345468U);
  // 45.687
  create_decimal_from_arr(&b, 0U, 3U, 0U, 0U, 45687U);
  // 31.9898
  create_decimal_from_arr(&ans, 0U, 4U, 0U, 0U, 319898U);

  status = s21_mod(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_divisor_bigger) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 12412525
  create_decimal_from_arr(&a, 0U, 0U, 0U, 0U, 12412525U);
  // 2352436135
  create_decimal_from_arr(&b, 0U, 0U, 0U, 0U, 2352436135U);
  // 12412525
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 12412525U);

  status = s21_mod(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_smol) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 6.4640546E-7
  create_decimal_from_arr(&a, 0U, 14U, 0U, 0U, 64640546U);
  // 4.684E-9
  create_decimal_from_arr(&b, 0U, 12U, 0U, 0U, 4684U);
  // 1.346E-11
  create_decimal_from_arr(&ans, 0U, 14U, 0U, 0U, 1346U);

  status = s21_mod(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_big_to_smol) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 79228162514264337593543950335
  create_decimal_from_arr(&a, 0U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // 0.1
  create_decimal_from_arr(&b, 0U, 2U, 0U, 0U, 1U);
  // 0.0
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 0U);

  status = s21_mod(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_zero_dividend) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 0
  create_decimal_from_arr(&a, 0U, 0U, 0U, 0U, 0U);
  // 8645
  create_decimal_from_arr(&b, 0U, 0U, 0U, 0U, 8645U);
  // 0
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 0U);

  status = s21_mod(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_big_same) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 79228162514264337593543950335
  create_decimal_from_arr(&a, 0U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // 79228162514264337593543950335
  create_decimal_from_arr(&b, 0U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // 0
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 0U);

  status = s21_mod(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_divisor_one) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 1241.2352623
  create_decimal_from_arr(&a, 0U, 7U, 0U, 2U, 3822418031U);
  // 1.000000000
  create_decimal_from_arr(&b, 0U, 8U, 0U, 0U, 100000000U);
  // 0.2352623
  create_decimal_from_arr(&ans, 0U, 7U, 0U, 0U, 2352623U);

  status = s21_mod(a, b, &res_dec);
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

  status = s21_mod(a, b, &res_dec);
  ck_assert((status == DIV_BY_ZERO));
}
END_TEST

START_TEST(test_minus1) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // -5468
  create_decimal_from_arr(&a, 1U, 0U, 0U, 0U, 5468U);
  // 3
  create_decimal_from_arr(&b, 0U, 0U, 0U, 0U, 3U);
  // -2
  create_decimal_from_arr(&ans, 1U, 0U, 0U, 0U, 2U);

  status = s21_mod(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_minus2) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // -5468
  create_decimal_from_arr(&a, 1U, 0U, 0U, 0U, 5468U);
  // -3
  create_decimal_from_arr(&b, 1U, 0U, 0U, 0U, 3U);
  // -2
  create_decimal_from_arr(&ans, 1U, 0U, 0U, 0U, 2U);

  status = s21_mod(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_minus3) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 5468
  create_decimal_from_arr(&a, 0U, 0U, 0U, 0U, 5468U);
  // -3
  create_decimal_from_arr(&b, 1U, 0U, 0U, 0U, 3U);
  // -2
  create_decimal_from_arr(&ans, 1U, 0U, 0U, 0U, 2U);

  status = s21_mod(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

Suite *test_mod() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Mod");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_mod);
  tcase_add_test(tc_core, test_divisor_bigger);
  tcase_add_test(tc_core, test_smol);
  tcase_add_test(tc_core, test_big_to_smol);
  tcase_add_test(tc_core, test_zero_dividend);
  tcase_add_test(tc_core, test_big_same);
  tcase_add_test(tc_core, test_divisor_one);
  tcase_add_test(tc_core, test_divisor_is_zero);
  tcase_add_test(tc_core, test_minus1);
  tcase_add_test(tc_core, test_minus2);
  tcase_add_test(tc_core, test_minus3);

  suite_add_tcase(s, tc_core);

  return s;
}