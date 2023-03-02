#include "test.h"

START_TEST(test_s21_is_not_equal_equally) {
  int status;
  s21_decimal a, b;
  create_decimal_from_arr(&a, 1U, 0U, 555U, 2U, 1U);
  create_decimal_from_arr(&b, 1U, 0U, 555U, 2U, 1U);
  status = s21_is_not_equal(a, b);
  ck_assert(status == FALSE);
}
END_TEST

START_TEST(test_s21_is_not_equal_equally2) {
  int status;
  s21_decimal a, b;
  create_decimal_from_arr(&a, 0U, 27U, 0, 0, 0);
  create_decimal_from_arr(&b, 1U, 27U, 0, 0, 0);
  status = s21_is_not_equal(a, b);
  ck_assert(status == FALSE);
}
END_TEST

START_TEST(test_s21_is_not_equal_equally3) {
  int status;
  s21_decimal a, b;
  create_decimal_from_arr(&a, 1U, 0U, 0, 0, 0);
  create_decimal_from_arr(&b, 0U, 0U, 0, 0, 0);
  status = s21_is_not_equal(a, b);
  ck_assert(status == FALSE);
}
END_TEST

START_TEST(test_s21_is_not_equal_more) {
  int status;
  s21_decimal a, b;
  // 12345.7890
  create_decimal_from_arr(&a, 0U, 3U, 0U, 0U, 12345789U);
  // 1234.5678910
  create_decimal_from_arr(&b, 0U, 6U, 0U, 0U, 1234567891U);
  status = s21_is_not_equal(a, b);
  ck_assert(status == TRUE);
}
END_TEST

START_TEST(test_s21_is_not_equal_more2) {
  int status;
  s21_decimal a, b;
  // -55555.111
  create_decimal_from_arr(&a, 1U, 3U, 0U, 0U, 55555111U);
  // -444443.1234567890
  create_decimal_from_arr(&b, 1U, 9U, 0U, 103479U, 4202634005U);
  status = s21_is_not_equal(a, b);
  ck_assert(status == TRUE);
}
END_TEST

START_TEST(test_s21_is_not_equal_more3) {
  int status;
  s21_decimal a, b;
  // 123.456
  create_decimal_from_arr(&a, 0U, 3U, 0U, 0U, 123456U);
  // 123.455
  create_decimal_from_arr(&b, 0U, 3U, 0U, 0U, 123455U);
  status = s21_is_not_equal(a, b);
  ck_assert(status == TRUE);
}
END_TEST

START_TEST(test_s21_is_not_equal_less) {
  int status;
  s21_decimal a, b;
  // -1234567890.555
  create_decimal_from_arr(&a, 1U, 3U, 0U, 287U, 1912276603U);
  // 1
  create_decimal_from_arr(&b, 0U, 0U, 0U, 0U, 1U);
  status = s21_is_not_equal(a, b);
  ck_assert(status == TRUE);
}
END_TEST

START_TEST(test_s21_is_not_equal_less2) {
  int status;
  s21_decimal a, b;
  create_decimal_from_arr(&a, 0U, 7U, _MAX_UINT_, _MAX_UINT_,
                          _MAX_UINT_ - 0.0000005);
  create_decimal_from_arr(&b, 0U, 7U, _MAX_UINT_, _MAX_UINT_, _MAX_UINT_);
  status = s21_is_not_equal(a, b);
  ck_assert(status == TRUE);
}
END_TEST

START_TEST(test_s21_is_not_equal_less3) {
  int status;
  s21_decimal a, b;
  create_decimal_from_arr(&a, 1U, 15U, _MAX_UINT_, _MAX_UINT_, _MAX_UINT_);
  create_decimal_from_arr(&b, 1U, 15U, _MAX_UINT_, _MAX_UINT_,
                          _MAX_UINT_ - 111);
  status = s21_is_not_equal(a, b);
  ck_assert(status == TRUE);
}
END_TEST

Suite *test_not_equal() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Is_not_equal");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_s21_is_not_equal_equally);
  tcase_add_test(tc_core, test_s21_is_not_equal_equally2);
  tcase_add_test(tc_core, test_s21_is_not_equal_equally3);
  tcase_add_test(tc_core, test_s21_is_not_equal_more);
  tcase_add_test(tc_core, test_s21_is_not_equal_more2);
  tcase_add_test(tc_core, test_s21_is_not_equal_more3);
  tcase_add_test(tc_core, test_s21_is_not_equal_less);
  tcase_add_test(tc_core, test_s21_is_not_equal_less2);
  tcase_add_test(tc_core, test_s21_is_not_equal_less3);
  suite_add_tcase(s, tc_core);

  return s;
}