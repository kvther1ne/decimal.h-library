#include "test.h"

START_TEST(test_s21_add) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 1
  create_decimal_from_arr(&a, 0U, 0U, 0U, 0U, 1U);
  // 2
  create_decimal_from_arr(&b, 0U, 0U, 0U, 0U, 2U);
  // 3
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 3U);

  status = s21_add(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_s21_add_minus) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // -12345
  create_decimal_from_arr(&a, 1U, 0U, 0U, 0U, 12345U);
  // 6789
  create_decimal_from_arr(&b, 0U, 0U, 0U, 0U, 6789U);
  // -5556
  create_decimal_from_arr(&ans, 1U, 0U, 0U, 0U, 5556U);

  status = s21_add(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_s21_add_minus_2) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 12345
  create_decimal_from_arr(&a, 0U, 0U, 0U, 0U, 12345U);
  // -6789
  create_decimal_from_arr(&b, 1U, 0U, 0U, 0U, 6789U);
  // 5556
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 5556U);

  status = s21_add(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_s21_add_neg) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // -12345.6
  create_decimal_from_arr(&a, 1U, 1U, 0U, 0U, 123456U);
  // -789.1
  create_decimal_from_arr(&b, 1U, 1U, 0U, 0U, 7891U);
  // -13134.7
  create_decimal_from_arr(&ans, 1U, 1U, 0U, 0U, 131347U);

  status = s21_add(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_s21_add_inf_minus) {
  int status, result;
  s21_decimal a, b, ans;
  s21_decimal res_dec = {0};
  // -inf
  create_decimal_from_arr(&a, 1U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // -20
  create_decimal_from_arr(&b, 1U, 0U, 0U, 0U, 20U);
  // 0
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 0U);

  status = s21_add(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == INF_MINUS) && (result == TRUE));
}
END_TEST

START_TEST(test_s21_add_inf_plus) {
  int status, result;
  s21_decimal a, b, ans;
  s21_decimal res_dec = {0};
  // 79228162514264337593543950335
  create_decimal_from_arr(&a, 0U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // 79228162514264337593543950335
  create_decimal_from_arr(&b, 0U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // 0
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 0U);

  status = s21_add(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == INF_PLUS) && (result == TRUE));
}
END_TEST

START_TEST(test_s21_add_inf_big) {
  int status, result;
  s21_decimal a, b, ans;
  s21_decimal res_dec = {0};
  // -inf
  create_decimal_from_arr(&a, 1U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // -inf
  create_decimal_from_arr(&b, 1U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // 0
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 0U);

  status = s21_add(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == INF_MINUS) && (result == TRUE));
}
END_TEST

Suite *test_add() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Add");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_add);
  tcase_add_test(tc_core, test_s21_add_minus);
  tcase_add_test(tc_core, test_s21_add_minus_2);
  tcase_add_test(tc_core, test_s21_add_neg);
  tcase_add_test(tc_core, test_s21_add_inf_minus);
  tcase_add_test(tc_core, test_s21_add_inf_plus);
  tcase_add_test(tc_core, test_s21_add_inf_big);

  suite_add_tcase(s, tc_core);

  return s;
}