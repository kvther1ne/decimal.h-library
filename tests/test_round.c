#include "test.h"

int is_exact_match(s21_decimal value1, s21_decimal value2);

//==========negate==========
START_TEST(test_negate_1) {
  int result, status;
  s21_decimal dec, res, ans;
  create_decimal_from_arr(&dec, 1U, 10U, __UINT32_MAX__, 231U, __UINT32_MAX__);
  status = s21_negate(dec, &res);
  create_decimal_from_arr(&ans, 0U, 10U, __UINT32_MAX__, 231U, __UINT32_MAX__);
  result = is_exact_match(res, ans);
  ck_assert(result && !status);
}
END_TEST

START_TEST(test_negate_2) {
  int result, status;
  s21_decimal dec, res, ans;
  create_decimal_from_arr(&dec, 0U, 1U, 123123, 231U, __UINT32_MAX__);
  status = s21_negate(dec, &res);
  create_decimal_from_arr(&ans, 1U, 1U, 123123, 231U, __UINT32_MAX__);
  result = is_exact_match(res, ans);
  ck_assert(result && !status);
}
END_TEST

START_TEST(test_negate_NULL) {
  int status;
  s21_decimal dec;
  create_decimal_from_arr(&dec, 0U, 28U, __UINT32_MAX__, __UINT32_MAX__,
                          __UINT32_MAX__);
  status = s21_negate(dec, NULL);
  ck_assert(status == ERROR_ROUND);
}
END_TEST

//============floor=========
START_TEST(test_floor_max) {
  int result, status;
  s21_decimal dec, res, ans;
  create_decimal_from_arr(&dec, 0U, 28U, __UINT32_MAX__, __UINT32_MAX__,
                          __UINT32_MAX__);
  status = s21_floor(dec, &res);
  create_decimal_from_arr(&ans, 0U, 0, 0, 0, 7U);
  result = is_exact_match(res, ans);
  ck_assert(result && !status);
}
END_TEST

START_TEST(test_floor_NULL) {
  int status;
  s21_decimal dec;
  create_decimal_from_arr(&dec, 0U, 28U, __UINT32_MAX__, __UINT32_MAX__,
                          __UINT32_MAX__);
  status = s21_floor(dec, NULL);
  ck_assert(status == ERROR_ROUND);
}
END_TEST

START_TEST(test_floor_zero_scale) {
  int result, status;
  s21_decimal dec, res;
  create_decimal_from_arr(&dec, 0U, 0U, __UINT32_MAX__, __UINT32_MAX__,
                          __UINT32_MAX__);
  status = s21_floor(dec, &res);
  result = is_exact_match(res, dec);
  ck_assert(result && !status);
}
END_TEST

START_TEST(test_floor_num_ten) {
  int result, status;
  s21_decimal dec, res, ans;
  create_decimal_from_arr(&dec, 1U, 3U, 0, 0, 1000U);
  status = s21_floor(dec, &res);
  create_decimal_from_arr(&ans, 1U, 0U, 0, 0, 1U);
  result = is_exact_match(res, ans);
  ck_assert(result && !status);
}
END_TEST

START_TEST(test_floor_num_minus) {
  int result, status;
  s21_decimal dec, res, ans;
  create_decimal_from_arr(&dec, 1U, 1U, 0, 0, 101U);
  status = s21_floor(dec, &res);
  create_decimal_from_arr(&ans, 1U, 0U, 0, 0, 11U);
  result = is_exact_match(res, ans);
  ck_assert(result && !status);
}
END_TEST

START_TEST(test_floor_distant) {
  int result, status;
  s21_decimal dec, res, ans;
  create_decimal_from_arr(&dec, 1U, 12U, 0U, 2328306U, 1874919425U);
  status = s21_floor(dec, &res);
  create_decimal_from_arr(&ans, 1U, 0U, 0, 0, 10001U);
  result = is_exact_match(res, ans);
  ck_assert(result && !status);
}
END_TEST

//==========truncate========
START_TEST(test_truncate_max) {
  int result, status;
  s21_decimal dec, res, ans;
  create_decimal_from_arr(&dec, 0U, 28U, __UINT32_MAX__, __UINT32_MAX__,
                          __UINT32_MAX__);
  status = s21_truncate(dec, &res);
  create_decimal_from_arr(&ans, 0U, 0, 0, 0, 7U);
  result = is_exact_match(res, ans);
  ck_assert(result && !status);
}
END_TEST

START_TEST(test_truncate_NULL) {
  int status;
  s21_decimal dec;
  create_decimal_from_arr(&dec, 0U, 28U, __UINT32_MAX__, __UINT32_MAX__,
                          __UINT32_MAX__);
  status = s21_truncate(dec, NULL);
  ck_assert(status == ERROR_ROUND);
}
END_TEST

START_TEST(test_truncate_zero_scale) {
  int result, status;
  s21_decimal dec, res;
  create_decimal_from_arr(&dec, 0U, 0U, __UINT32_MAX__, 0U, 0U);
  status = s21_truncate(dec, &res);
  result = is_exact_match(res, dec);
  ck_assert(result && !status);
}
END_TEST

START_TEST(test_truncate_num_ten) {
  int result, status;
  s21_decimal dec, res, ans;
  create_decimal_from_arr(&dec, 1U, 3U, 0, 0, 1000U);
  status = s21_truncate(dec, &res);
  create_decimal_from_arr(&ans, 1U, 0U, 0, 0, 1U);
  result = is_exact_match(res, ans);
  ck_assert(result && !status);
}
END_TEST

START_TEST(test_truncate_num_minus) {
  int result, status;
  s21_decimal dec, res, ans;
  create_decimal_from_arr(&dec, 1U, 1U, 0, 0, 101U);
  status = s21_truncate(dec, &res);
  create_decimal_from_arr(&ans, 1U, 0U, 0, 0, 10U);
  result = is_exact_match(res, ans);
  ck_assert(result && !status);
}
END_TEST

START_TEST(test_truncate_distant) {
  int result, status;
  s21_decimal dec, res, ans;
  create_decimal_from_arr(&dec, 1U, 12U, 0U, 2328306U, 1874919425U);
  status = s21_truncate(dec, &res);
  create_decimal_from_arr(&ans, 1U, 0U, 0, 0, 10000U);
  result = is_exact_match(res, ans);
  ck_assert(result && !status);
}
END_TEST

//============round=========
START_TEST(test_round_max) {
  int result, status;
  s21_decimal dec, res, ans;
  create_decimal_from_arr(&dec, 0U, 28U, __UINT32_MAX__, __UINT32_MAX__,
                          __UINT32_MAX__);
  status = s21_round(dec, &res);
  create_decimal_from_arr(&ans, 0U, 0, 0, 0, 8U);
  result = is_exact_match(res, ans);
  ck_assert(result && !status);
}
END_TEST

START_TEST(test_round_NULL) {
  int status;
  s21_decimal dec;
  create_decimal_from_arr(&dec, 0U, 28U, __UINT32_MAX__, __UINT32_MAX__,
                          __UINT32_MAX__);
  status = s21_round(dec, NULL);
  ck_assert(status == ERROR_ROUND);
}
END_TEST

START_TEST(test_round_zero_scale) {
  int result, status;
  s21_decimal dec, res;
  create_decimal_from_arr(&dec, 0U, 0U, __UINT32_MAX__, __UINT32_MAX__, 0U);
  status = s21_round(dec, &res);
  result = is_exact_match(res, dec);
  ck_assert(result && !status);
}
END_TEST

START_TEST(test_round_num_ten) {
  int result, status;
  s21_decimal dec, res, ans;
  create_decimal_from_arr(&dec, 1U, 3U, 0, 0, 1000U);
  status = s21_round(dec, &res);
  create_decimal_from_arr(&ans, 1U, 0U, 0, 0, 1U);
  result = is_exact_match(res, ans);
  ck_assert(result && !status);
}
END_TEST

START_TEST(test_round_distant) {
  int result, status;
  s21_decimal dec, res, ans;
  create_decimal_from_arr(&dec, 1U, 12U, 0U, 2328306U, 1874919425U);
  status = s21_round(dec, &res);
  create_decimal_from_arr(&ans, 1U, 0U, 0, 0, 10000U);
  result = is_exact_match(res, ans);
  ck_assert(result && !status);
}
END_TEST

START_TEST(test_round_num_rem_5_long_1) {
  int result, status;
  s21_decimal dec, res, ans;
  create_decimal_from_arr(&dec, 1U, 23U, 13552U, 2264118075U, 1749024769U);
  status = s21_round(dec, &res);
  create_decimal_from_arr(&ans, 1U, 0U, 0, 0, 3U);
  result = is_exact_match(res, ans);
  ck_assert(result && !status);
}
END_TEST

START_TEST(test_round_num_bank_5_up) {
  int result, status;
  s21_decimal dec, res, ans;
  create_decimal_from_arr(&dec, 1U, 23U, 8131U, 2217464304U, 1908408320U);
  status = s21_round(dec, &res);
  create_decimal_from_arr(&ans, 1U, 0U, 0, 0, 2U);
  result = is_exact_match(res, ans);
  ck_assert(result && !status);
}
END_TEST

START_TEST(test_round_num_bank_5_down) {
  int result, status;
  s21_decimal dec, res, ans;
  create_decimal_from_arr(&dec, 1U, 23U, 13552U, 2264118075U, 1749024768U);
  status = s21_round(dec, &res);
  create_decimal_from_arr(&ans, 1U, 0U, 0, 0, 2U);
  result = is_exact_match(res, ans);
  ck_assert(result && !status);
}
END_TEST

START_TEST(test_round_2) {
  int result, status;
  s21_decimal dec, res, ans;
  create_decimal_from_arr(&dec, 0U, 1U, 0U, 9U, 4294967291U);
  status = s21_round(dec, &res);
  create_decimal_from_arr(&ans, 0U, 0U, 0, 1U, 0);
  result = is_exact_match(res, ans);
  ck_assert(result && !status);
}
END_TEST

TCase* create_tcase_negate();
TCase* create_tcase_floor();
TCase* create_tcase_truncate();
TCase* create_tcase_round();

Suite* test_round() {
  Suite* s;

  s = suite_create("Round");
  suite_add_tcase(s, create_tcase_negate());
  suite_add_tcase(s, create_tcase_floor());
  suite_add_tcase(s, create_tcase_truncate());
  suite_add_tcase(s, create_tcase_round());

  return s;
}

TCase* create_tcase_negate() {
  TCase* result;
  result = tcase_create("negate");
  tcase_add_test(result, test_negate_1);
  tcase_add_test(result, test_negate_2);
  tcase_add_test(result, test_negate_NULL);
  return result;
}

TCase* create_tcase_floor() {
  TCase* tc_round_floor;
  tc_round_floor = tcase_create("floor");
  tcase_add_test(tc_round_floor, test_floor_max);
  tcase_add_test(tc_round_floor, test_floor_NULL);
  tcase_add_test(tc_round_floor, test_floor_zero_scale);
  tcase_add_test(tc_round_floor, test_floor_num_ten);
  tcase_add_test(tc_round_floor, test_floor_num_minus);
  tcase_add_test(tc_round_floor, test_floor_distant);
  return tc_round_floor;
}

TCase* create_tcase_truncate() {
  TCase* tc_round_truncate;
  tc_round_truncate = tcase_create("truncate");
  tcase_add_test(tc_round_truncate, test_truncate_max);
  tcase_add_test(tc_round_truncate, test_truncate_NULL);
  tcase_add_test(tc_round_truncate, test_truncate_zero_scale);
  tcase_add_test(tc_round_truncate, test_truncate_num_ten);
  tcase_add_test(tc_round_truncate, test_truncate_num_minus);
  tcase_add_test(tc_round_truncate, test_truncate_distant);
  return tc_round_truncate;
}

TCase* create_tcase_round() {
  TCase* tc_round_round;
  tc_round_round = tcase_create("round");
  tcase_add_test(tc_round_round, test_round_max);
  tcase_add_test(tc_round_round, test_round_NULL);
  tcase_add_test(tc_round_round, test_round_zero_scale);
  tcase_add_test(tc_round_round, test_round_num_ten);
  tcase_add_test(tc_round_round, test_round_distant);
  tcase_add_test(tc_round_round, test_round_num_rem_5_long_1);
  tcase_add_test(tc_round_round, test_round_num_bank_5_up);
  tcase_add_test(tc_round_round, test_round_num_bank_5_down);
  tcase_add_test(tc_round_round, test_round_2);
  return tc_round_round;
}

int is_exact_match(s21_decimal value1, s21_decimal value2) {
  unsigned int res = 0;
  for (int i = 0; i < 4; i++) {
    res |= value1.bits[i] ^ value2.bits[i];
  }
  return (res == 0);
}
