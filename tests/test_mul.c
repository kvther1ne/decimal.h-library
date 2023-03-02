#include "test.h"

Suite *test_multiply();

START_TEST(test_multiply_zero) {
  int result, status_mul;
  s21_decimal mul1 = {0}, mul2 = {0}, res_dec, answer;
  create_decimal_from_arr(&mul1, 0U, 0U, 0U, 0U, __UINT32_MAX__);
  create_decimal_from_arr(&mul2, 0U, 0U, 0U, 0U, 0U);
  status_mul = s21_mul(mul1, mul2, &res_dec);
  create_decimal_from_arr(&answer, 0U, 0U, 0U, 0U, 0U);
  result = s21_is_equal(res_dec, answer);
  ck_assert(result && !status_mul);
}
END_TEST

START_TEST(test_multiply_inf_plus) {
  int status_mul;
  s21_decimal mul1 = {0}, mul2 = {0}, res_dec;
  create_decimal_from_arr(&mul1, 0U, 0U, __UINT32_MAX__, __UINT32_MAX__,
                          __UINT32_MAX__);
  create_decimal_from_arr(&mul2, 0U, 0U, 0U, 0U, __UINT32_MAX__);
  status_mul = s21_mul(mul1, mul2, &res_dec);
  ck_assert(status_mul == INF_PLUS);
}
END_TEST

START_TEST(test_multiply_inf_minus) {
  int status_mul;
  s21_decimal mul1 = {0}, mul2 = {0}, res_dec;
  create_decimal_from_arr(&mul1, 1U, 0U, __UINT32_MAX__, __UINT32_MAX__,
                          __UINT32_MAX__);
  create_decimal_from_arr(&mul2, 0U, 0U, 0U, 0U, __UINT32_MAX__);
  status_mul = s21_mul(mul1, mul2, &res_dec);
  ck_assert(status_mul == INF_MINUS);
}
END_TEST

START_TEST(test_multiply_1) {
  int status_mul, result;
  s21_decimal mul1 = {0}, mul2 = {0}, res_dec, answer;
  create_decimal_from_arr(&mul1, 1U, 10U, __UINT32_MAX__, __UINT32_MAX__,
                          __UINT32_MAX__);
  create_decimal_from_arr(&mul2, 0U, 0U, 0U, 0U, __UINT32_MAX__);
  status_mul = s21_mul(mul1, mul2, &res_dec);
  create_decimal_from_arr(&answer, 1U, 0U, 1844674406U, 4043533175U,
                          4223842087U);
  result = s21_is_equal(res_dec, answer);
  ck_assert((status_mul == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_multiply_2) {
  int status_mul, result;
  s21_decimal mul1 = {0}, mul2 = {0}, res_dec, answer;
  create_decimal_from_arr(&mul1, 1U, 10U, __UINT32_MAX__, 0, 0);
  create_decimal_from_arr(&mul2, 0U, 0U, 0U, 0U, __UINT32_MAX__);
  status_mul = s21_mul(mul1, mul2, &res_dec);
  create_decimal_from_arr(&answer, 1U, 0U, 1844674406U, 2198858769U,
                          180308912U);
  result = s21_is_equal(res_dec, answer);
  ck_assert((status_mul == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_multiply_scale) {
  int status_mul, result;
  s21_decimal mul1 = {0}, mul2 = {0}, res_dec, answer;
  create_decimal_from_arr(&mul1, 1U, 10U, 0U, 1U, 0U);
  create_decimal_from_arr(&mul2, 0U, 10U, 0U, 1U, 0U);
  status_mul = s21_mul(mul1, mul2, &res_dec);
  create_decimal_from_arr(&answer, 1U, 20U, 1U, 0, 0);
  result = s21_is_equal(res_dec, answer);
  ck_assert((status_mul == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_multiply_scale_2) {
  int status_mul, result;
  s21_decimal mul1 = {0}, mul2 = {0}, res_dec, answer;
  create_decimal_from_arr(&mul1, 1U, 10U, 1U, 0U, 0U);
  // print_decimal(mul1);
  create_decimal_from_arr(&mul2, 1U, 10U, 1U, 0U, 0U);
  // print_decimal(mul2);
  status_mul = s21_mul(mul1, mul2, &res_dec);
  // print_decimal(res_dec);
  create_decimal_from_arr(&answer, 0U, 10U, 1844674407U, 1593240287U,
                          1522115079U);
  result = s21_is_equal(res_dec, answer);
  ck_assert((status_mul == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_multiply_3) {
  int status_mul, result;
  s21_decimal mul1 = {0}, mul2 = {0}, res_dec, answer;
  create_decimal_from_arr(&mul1, 1U, 10U, __UINT32_MAX__, __UINT32_MAX__,
                          __UINT32_MAX__);
  create_decimal_from_arr(&mul2, 0U, 0U, 0U, 0U, 1U);
  status_mul = s21_mul(mul1, mul2, &res_dec);
  create_decimal_from_arr(&answer, 1U, 10U, __UINT32_MAX__, __UINT32_MAX__,
                          __UINT32_MAX__);
  result = s21_is_equal(res_dec, answer);
  ck_assert((status_mul == OK) && (result == TRUE));
}
END_TEST

Suite *test_multiply() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Multiply");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_multiply_zero);
  tcase_add_test(tc_core, test_multiply_inf_plus);
  tcase_add_test(tc_core, test_multiply_inf_minus);
  tcase_add_test(tc_core, test_multiply_1);
  tcase_add_test(tc_core, test_multiply_2);
  tcase_add_test(tc_core, test_multiply_scale);
  tcase_add_test(tc_core, test_multiply_scale_2);
  tcase_add_test(tc_core, test_multiply_3);
  suite_add_tcase(s, tc_core);

  return s;
}
