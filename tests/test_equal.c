#include "test.h"

Suite *test_equal();

START_TEST(test_equal_1) {
  int result;
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 1024U * 10U;
  dec1.bits[1] = 0U;
  dec1.bits[2] = 0U;
  dec1.bits[3] = (1U << 31) + (1U << 16);

  dec2.bits[0] = 1024U * 1U;
  dec2.bits[1] = 0U;
  dec2.bits[2] = 0U;
  dec2.bits[3] = (1U << 31) + (0U << 16);

  result = s21_is_equal(dec1, dec2);
  ck_assert(result);
}
END_TEST

START_TEST(test_equal_zeros) {
  int result;
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 0U;
  dec1.bits[1] = 0U;
  dec1.bits[2] = 0U;
  dec1.bits[3] = (0U << 31) + (10U << 16);

  dec2.bits[0] = 0U;
  dec2.bits[1] = 0U;
  dec2.bits[2] = 0U;
  dec2.bits[3] = (0U << 31) + (0U << 16);

  result = s21_is_equal(dec1, dec2);
  ck_assert(result);
}
END_TEST

START_TEST(test_equal_sign) {
  int result;
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 0U;
  dec1.bits[1] = 12U;
  dec1.bits[2] = 0U;
  dec1.bits[3] = (0U << 31) + (10U << 16);

  dec2.bits[0] = 0U;
  dec2.bits[1] = 12U;
  dec2.bits[2] = 0U;
  dec2.bits[3] = (1U << 31) + (0U << 16);

  result = s21_is_equal(dec1, dec2);
  ck_assert(result == 0);
}
END_TEST

START_TEST(test_equal_sign_zero) {
  int result;
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 0U;
  dec1.bits[1] = 0U;
  dec1.bits[2] = 0U;
  dec1.bits[3] = (0U << 31) + (10U << 16);

  dec2.bits[0] = 0U;
  dec2.bits[1] = 0U;
  dec2.bits[2] = 0U;
  dec2.bits[3] = (1U << 31) + (0U << 16);

  result = s21_is_equal(dec1, dec2);
  ck_assert(result);
}
END_TEST

START_TEST(test_equal_4) {
  int result;
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 112314U * 10U;
  dec1.bits[1] = 0U;
  dec1.bits[2] = 0U;
  dec1.bits[3] = (1U << 31) + (2U << 16);

  dec2.bits[0] = 112314U * 10U;
  dec2.bits[1] = 0U;
  dec2.bits[2] = 0U;
  dec2.bits[3] = (1U << 31) + (0U << 16);

  result = s21_is_equal(dec1, dec2);
  ck_assert(result == 0);
}
END_TEST

START_TEST(test_equal_5) {
  int result;
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 123U * 12U;
  dec1.bits[1] = 123U * 12U;
  dec1.bits[2] = 123U * 12U;
  dec1.bits[3] = (1U << 31) + (2U << 16);

  dec2.bits[0] = 123U * 12U;
  dec2.bits[1] = 123U * 12U;
  dec2.bits[2] = 123U * 12U;
  dec2.bits[3] = (1U << 31) + (2U << 16);

  result = s21_is_equal(dec1, dec2);
  ck_assert(result);
}
END_TEST

START_TEST(test_equal_6) {
  int result;
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 0b00000011010110001110111110100011;
  dec1.bits[1] = 0b00000000000000000000101101001010;
  dec1.bits[2] = 0U;
  dec1.bits[3] = (1U << 31) + (1U << 16);

  dec2.bits[0] = 0b00000011010110001110111110100011;
  dec2.bits[1] = 0b00000000000000000000101101001010;
  dec2.bits[2] = 0U;
  dec2.bits[3] = (1U << 31) + (1U << 16);

  result = s21_is_equal(dec1, dec2);
  ck_assert(result == TRUE);
}
END_TEST

Suite *test_equal() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Is_equal");
  tc_core = tcase_create("Equal");

  tcase_add_test(tc_core, test_equal_1);
  tcase_add_test(tc_core, test_equal_zeros);
  tcase_add_test(tc_core, test_equal_sign);
  tcase_add_test(tc_core, test_equal_sign_zero);
  tcase_add_test(tc_core, test_equal_4);
  tcase_add_test(tc_core, test_equal_5);
  tcase_add_test(tc_core, test_equal_6);
  // tcase_add_test(tc_core, test_equal_zero_zero);
  // tcase_add_test(tc_core, test_from_int_to_decimal_zero);
  suite_add_tcase(s, tc_core);

  return s;
}