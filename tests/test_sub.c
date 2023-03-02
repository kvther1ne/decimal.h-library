#include "test.h"

START_TEST(test_subtraction) {
  int status_sub, result_ans;
  s21_decimal value1 = {0}, value2 = {0}, result, answer;
  create_decimal_from_arr(&value1, 0U, 0U, __UINT32_MAX__, __UINT32_MAX__,
                          __UINT32_MAX__);
  create_decimal_from_arr(&value2, 0U, 0U, __UINT32_MAX__, __UINT32_MAX__,
                          __UINT32_MAX__);
  status_sub = s21_sub(value1, value2, &result);
  create_decimal_from_arr(&answer, 0U, 0U, 0U, 0U, 0U);
  result_ans = s21_is_equal(result, answer);
  ck_assert(status_sub == OK && result_ans == TRUE);
}
END_TEST

START_TEST(test_s21_sub) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 12345.000000043
  create_decimal_from_arr(&a, 0U, 9U, 0U, 2874U, 1263991339U);
  // 0.0000021
  create_decimal_from_arr(&b, 0U, 7U, 0U, 0U, 21U);
  // 12344.999997943
  create_decimal_from_arr(&ans, 0U, 9U, 0U, 2874U, 1263989239U);

  status = s21_sub(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_s21_sub1) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 125125.213425163554
  create_decimal_from_arr(&a, 0U, 12U, 0U, 29132983U, 4205239586U);
  // 564766473883.12
  create_decimal_from_arr(&b, 0U, 2U, 0U, 13149U, 2122413208U);
  // -564766348757.906574836446
  create_decimal_from_arr(&ans, 1U, 12U, 30616U, 193761013U, 867730142U);

  status = s21_sub(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_s21_sub2) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // -10000.123456787899
  create_decimal_from_arr(&a, 1U, 12U, 0U, 2328335U, 777655739U);
  // -1234567889
  create_decimal_from_arr(&b, 1U, 0U, 0U, 0U, 1234567889U);
  // 1234557888.876543212101
  create_decimal_from_arr(&ans, 0U, 12U, 66U, 3975066359U, 378010181U);

  status = s21_sub(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_s21_sub3) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // -12345.3
  create_decimal_from_arr(&a, 1U, 1U, 0U, 0U, 123453U);
  // 1241251152215
  create_decimal_from_arr(&b, 0U, 0U, 0U, 289U, 5603671U);
  // -1241251164560.3
  create_decimal_from_arr(&ans, 1U, 1U, 0U, 2890U, 56160163U);

  status = s21_sub(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_s21_sub4) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // -125216.4373747334
  create_decimal_from_arr(&a, 1U, 10U, 0U, 291542U, 1018336902U);
  // 0
  create_decimal_from_arr(&b, 0U, 0U, 0U, 0U, 0U);
  // -125216.4373747334
  create_decimal_from_arr(&ans, 1U, 10U, 0U, 291542U, 1018336902U);

  status = s21_sub(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_s21_sub5) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 10
  create_decimal_from_arr(&a, 0U, 0U, 0U, 0U, 10U);
  // -25
  create_decimal_from_arr(&b, 1U, 0U, 0U, 0U, 25U);
  // 35
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 35U);

  status = s21_sub(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_s21_sub_inf_plus) {
  int status, result;
  s21_decimal a, b, ans;
  s21_decimal res_dec = {0};
  // 4294967295
  create_decimal_from_arr(&a, 0U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // -20
  create_decimal_from_arr(&b, 1U, 0U, 0U, 0U, 20U);
  // 0
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 0U);

  status = s21_sub(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == INF_PLUS) && (result == TRUE));
}
END_TEST

START_TEST(test_s21_sub_inf_minus) {
  int status, result;
  s21_decimal a, b, ans;
  s21_decimal res_dec = {0};
  // -79228162514264337593543950335
  create_decimal_from_arr(&a, 1U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // 79228162514264337593543950335
  create_decimal_from_arr(&b, 0U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // 0
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 0U);

  status = s21_sub(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == INF_MINUS) && (result == TRUE));
}
END_TEST

START_TEST(test_s21_sub_bank_round) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 79228162514264337593543950335
  create_decimal_from_arr(&a, 0U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // 0.6
  create_decimal_from_arr(&b, 0U, 1U, 0U, 0U, 6U);
  // 79228162514264337593543950334
  create_decimal_from_arr(&ans, 0U, 0U, 4294967295U, 4294967295U, 4294967294U);

  status = s21_sub(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_s21_sub_bank_round_with_inf_plus) {
  int status, result;
  s21_decimal a, b, ans;
  s21_decimal res_dec = {0};
  // 79228162514264337593543950335
  create_decimal_from_arr(&a, 0U, 0U, 4294967295U, 4294967295U, 4294967295U);
  // -0.6
  create_decimal_from_arr(&b, 1U, 1U, 0U, 0U, 6U);
  // 0
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 0U);

  status = s21_sub(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == INF_PLUS) && (result == TRUE));
}
END_TEST

START_TEST(test_s21_aboba1) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 12345
  create_decimal_from_arr(&a, 0U, 0U, 0U, 0U, 12345U);
  // 6789
  create_decimal_from_arr(&b, 0U, 0U, 0U, 0U, 6789U);
  // 5556
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 5556U);

  status = s21_sub(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_s21_aboba2) {
  int status, result;
  s21_decimal a, b, ans, res_dec;
  // 635609343049897858478801.18022
  create_decimal_from_arr(&a, 0U, 5U, 3445645152U, 4011145482U, 1427795718U);
  // 3.9537176089388204189268624474
  create_decimal_from_arr(&b, 0U, 28U, 2143314610U, 2159645155U, 2456863834U);
  // 635609343049897858478797.22650
  create_decimal_from_arr(&ans, 0U, 4U, 344564515U, 1260108007U, 1860726953U);

  status = s21_sub(a, b, &res_dec);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

Suite *test_sub() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Subtraction");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_subtraction);
  tcase_add_test(tc_core, test_s21_sub);
  tcase_add_test(tc_core, test_s21_sub1);
  tcase_add_test(tc_core, test_s21_sub2);
  tcase_add_test(tc_core, test_s21_sub3);
  tcase_add_test(tc_core, test_s21_sub4);
  tcase_add_test(tc_core, test_s21_sub5);
  tcase_add_test(tc_core, test_s21_sub_inf_plus);
  tcase_add_test(tc_core, test_s21_sub_inf_minus);
  tcase_add_test(tc_core, test_s21_sub_bank_round);
  tcase_add_test(tc_core, test_s21_sub_bank_round_with_inf_plus);
  tcase_add_test(tc_core, test_s21_aboba1);
  tcase_add_test(tc_core, test_s21_aboba2);
  suite_add_tcase(s, tc_core);

  return s;
}