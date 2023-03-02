#include "test.h"

int eq_dec_int(int a, s21_decimal b) {
  unsigned int flag = 0;
  if (a < 0) {
    a = -a;
    flag = 1;
  }
  return (b.bits[3] == ((unsigned int)flag << 31)) &&
         (b.bits[0] == (unsigned int)a);
}

START_TEST(test_fl_to_dec_1) {
  int status, result;
  float num_fl;
  s21_decimal ans, res_dec;

  num_fl = 123456789e-0f;

  status = s21_from_float_to_decimal(num_fl, &res_dec);
  // 123456800
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 123456800U);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_fl_to_dec_2) {
  int status, result;
  float num_fl;
  s21_decimal ans, res_dec;

  num_fl = 12345675.f;

  status = s21_from_float_to_decimal(num_fl, &res_dec);
  // 12345680
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 12345680U);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_fl_to_dec_3) {
  int status, result;
  float num_fl;
  s21_decimal ans, res_dec;

  num_fl = 12345665e-0f;

  status = s21_from_float_to_decimal(num_fl, &res_dec);
  // 12345660
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 12345660U);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_fl_to_dec_4) {
  int status, result;
  float num_fl;
  s21_decimal ans, res_dec;

  num_fl = 1e-28f;

  status = s21_from_float_to_decimal(num_fl, &res_dec);
  // 0
  create_decimal_from_arr(&ans, 0U, 28U, 0U, 0U, 1U);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_fl_to_dec_5) {
  int status, result;
  float num_fl;
  s21_decimal ans, res_dec;

  num_fl = 12345678912345678e-5f;

  status = s21_from_float_to_decimal(num_fl, &res_dec);
  // 123456800000
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 28U, 3197715712U);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_fl_to_dec_6) {
  int status, result;
  float num_fl;
  s21_decimal ans, res_dec;

  num_fl = 987654321e7f;

  status = s21_from_float_to_decimal(num_fl, &res_dec);
  // 9876544000000000
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 2299562U, 414875648U);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_fl_to_dec_7) {
  int status, result;
  float num_fl;
  s21_decimal ans, res_dec;

  num_fl = 100e-2f;

  status = s21_from_float_to_decimal(num_fl, &res_dec);
  // 1
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 1U);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_fl_to_dec_8) {
  int status, result;
  float num_fl;
  s21_decimal ans, res_dec;

  num_fl = -123456789e-20f;

  status = s21_from_float_to_decimal(num_fl, &res_dec);
  // 1.234568E-12
  create_decimal_from_arr(&ans, 1U, 18U, 0U, 0U, 1234568U);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_fl_to_dec_9) {
  int status, result;
  float num_fl;
  s21_decimal ans, res_dec;

  num_fl = 1e-29f;

  status = s21_from_float_to_decimal(num_fl, &res_dec);
  // 0
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 0U);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == CONVERSION_ERROR) && (result == TRUE));
}
END_TEST

START_TEST(test_fl_to_dec_10) {
  int status, result;
  float num_fl;
  s21_decimal ans, res_dec;

  num_fl = 7922816e22f;

  status = s21_from_float_to_decimal(num_fl, &res_dec);
  // 7.922816E+28
  create_decimal_from_arr(&ans, 0U, 0U, 4294967159U, 3012735514U, 536870912U);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_fl_to_dec_11) {
  int status;
  float num_fl;
  s21_decimal res_dec;

  num_fl = 7922817e22f;

  status = s21_from_float_to_decimal(num_fl, &res_dec);
  ck_assert((status == CONVERSION_ERROR));
}
END_TEST

START_TEST(test_fl_to_dec_12) {
  int status, result;
  float num_fl;
  s21_decimal ans, res_dec;

  num_fl = 999.999999f;

  status = s21_from_float_to_decimal(num_fl, &res_dec);
  // 1000
  create_decimal_from_arr(&ans, 0U, 0U, 0U, 0U, 1000U);
  result = s21_is_equal(res_dec, ans);
  ck_assert((status == OK) && (result == TRUE));
}
END_TEST

START_TEST(test_fl_to_dec_inf_plus) {
  int status;
  float num_fl;
  s21_decimal res_dec;

  num_fl = INFINITY;

  status = s21_from_float_to_decimal(num_fl, &res_dec);
  ck_assert((status == CONVERSION_ERROR));
}
END_TEST

START_TEST(test_fl_to_dec_inf_minus) {
  int status;
  float num_fl;
  s21_decimal res_dec;

  num_fl = -INFINITY;

  status = s21_from_float_to_decimal(num_fl, &res_dec);
  ck_assert((status == CONVERSION_ERROR));
}
END_TEST

START_TEST(test_fl_to_dec_nan) {
  int status;
  float num_fl;
  s21_decimal res_dec;

  num_fl = NAN;

  status = s21_from_float_to_decimal(num_fl, &res_dec);
  ck_assert((status == CONVERSION_ERROR));
}
END_TEST

START_TEST(test_fl_to_dec_null) {
  int status;
  float num_fl;

  num_fl = NAN;

  status = s21_from_float_to_decimal(num_fl, NULL);
  ck_assert((status == CONVERSION_ERROR));
}
END_TEST
//================int_to_dec===========

START_TEST(test_int_to_dec_max_int) {
  int status, num_1 = INT32_MAX;
  s21_decimal test_dec;
  status = s21_from_int_to_decimal(num_1, &test_dec);
  ck_assert(eq_dec_int(num_1, test_dec) && status == OK);
}
END_TEST

START_TEST(test_int_to_dec_min_int) {
  int status, num_1 = INT32_MIN;
  s21_decimal test_dec;
  status = s21_from_int_to_decimal(num_1, &test_dec);
  ck_assert(eq_dec_int(num_1, test_dec) && status == OK);
}
END_TEST

START_TEST(test_int_to_dec_zero) {
  int status, num_1 = 0;
  s21_decimal test_dec;
  status = s21_from_int_to_decimal(num_1, &test_dec);
  ck_assert(eq_dec_int(num_1, test_dec) && status == OK);
}
END_TEST

START_TEST(test_int_to_dec_null) {
  int status, num_1 = 20123;
  status = s21_from_int_to_decimal(num_1, NULL);
  ck_assert(status == CONVERSION_ERROR);
}
END_TEST

//================dec_to_int===========

START_TEST(test_decimal_to_int_1) {
  int status, result;
  s21_decimal inp;
  // 123.123123123
  create_decimal_from_arr(&inp, 0U, 9U, 0U, 28U, 2864038835U);

  status = s21_from_decimal_to_int(inp, &result);
  ck_assert((status == OK) && (result == 123));
}
END_TEST

START_TEST(test_decimal_to_int_2) {
  int status, result;
  s21_decimal inp;
  // -300.01111100000
  create_decimal_from_arr(&inp, 1U, 6U, 0U, 0U, 300011111U);

  status = s21_from_decimal_to_int(inp, &result);
  ck_assert((status == OK) && (result == -300));
}
END_TEST

START_TEST(test_decimal_to_int_3) {
  int status, result;
  s21_decimal inp;
  // 4294967295
  create_decimal_from_arr(&inp, 1U, 0U, 0U, 0U, __UINT32_MAX__);

  status = s21_from_decimal_to_int(inp, &result);
  ck_assert((status == CONVERSION_ERROR));
}
END_TEST

START_TEST(test_decimal_to_int_4) {
  int status;
  s21_decimal inp;
  // 4294967295
  create_decimal_from_arr(&inp, 1U, 0U, 0U, 0U, __UINT32_MAX__);

  status = s21_from_decimal_to_int(inp, NULL);
  ck_assert((status == CONVERSION_ERROR));
}
END_TEST

//================dec_to_float=========
START_TEST(test_decimal_to_float_1) {
  int status;
  char res_chr[20];
  float result;
  s21_decimal inp;
  // 1234567890
  create_decimal_from_arr(&inp, 0U, 0U, 0U, 0U, 1234567890U);

  status = s21_from_decimal_to_float(inp, &result);
  sprintf(((char *)res_chr), "%e", result);
  char answer[] = "1.234568e+09";
  ck_assert((status == OK) && (strcmp(res_chr, answer) == 0));
}
END_TEST

START_TEST(test_decimal_to_float_2) {
  int status;
  s21_decimal inp;
  create_decimal_from_arr(&inp, 0U, 0U, 0U, 0U, 1234567890U);

  status = s21_from_decimal_to_float(inp, NULL);
  ck_assert(status == CONVERSION_ERROR);
}
END_TEST

START_TEST(test_decimal_to_float_3) {
  int status;
  char res_chr[20];
  float result;
  s21_decimal inp;
  // 1e-28
  create_decimal_from_arr(&inp, 1U, 28U, 0U, 0U, 1);

  status = s21_from_decimal_to_float(inp, &result);
  sprintf(((char *)res_chr), "%e", result);
  char answer[] = "-1.000000e-28";
  ck_assert((status == OK) && (strcmp(res_chr, answer) == 0));
}
END_TEST

START_TEST(test_decimal_to_float_4) {
  int status;
  char res_chr[20];
  float result;
  s21_decimal inp;
  // 1e-28
  create_decimal_from_arr(&inp, 1U, 0U, __UINT32_MAX__, __UINT32_MAX__,
                          __UINT32_MAX__);

  status = s21_from_decimal_to_float(inp, &result);
  sprintf(((char *)res_chr), "%e", result);
  char answer[] = "-7.922816e+28";
  ck_assert((status == OK) && (strcmp(res_chr, answer) == 0));
}
END_TEST

START_TEST(test_decimal_to_float_5) {
  int status;
  char res_chr[20];
  float result;
  s21_decimal inp;
  // 55555555
  create_decimal_from_arr(&inp, 0U, 0U, 0U, 0U, 55555555U);

  status = s21_from_decimal_to_float(inp, &result);
  sprintf(((char *)res_chr), "%e", result);
  char answer[] = "5.555556e+07";
  ck_assert((status == OK) && (strcmp(res_chr, answer) == 0));
}
END_TEST

Suite *test_from_int_to_decimal() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("from_int_to_decimal");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_int_to_dec_max_int);
  tcase_add_test(tc_core, test_int_to_dec_min_int);
  tcase_add_test(tc_core, test_int_to_dec_zero);
  tcase_add_test(tc_core, test_int_to_dec_null);
  suite_add_tcase(s, tc_core);

  return s;
}

Suite *test_from_float_to_decimal() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("from_float_to_decimal");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_fl_to_dec_1);
  tcase_add_test(tc_core, test_fl_to_dec_2);
  tcase_add_test(tc_core, test_fl_to_dec_3);
  tcase_add_test(tc_core, test_fl_to_dec_4);
  tcase_add_test(tc_core, test_fl_to_dec_5);
  tcase_add_test(tc_core, test_fl_to_dec_6);
  tcase_add_test(tc_core, test_fl_to_dec_7);
  tcase_add_test(tc_core, test_fl_to_dec_8);
  tcase_add_test(tc_core, test_fl_to_dec_9);
  tcase_add_test(tc_core, test_fl_to_dec_10);
  tcase_add_test(tc_core, test_fl_to_dec_11);
  tcase_add_test(tc_core, test_fl_to_dec_12);
  tcase_add_test(tc_core, test_fl_to_dec_inf_plus);
  tcase_add_test(tc_core, test_fl_to_dec_inf_minus);
  tcase_add_test(tc_core, test_fl_to_dec_nan);
  tcase_add_test(tc_core, test_fl_to_dec_null);
  suite_add_tcase(s, tc_core);

  return s;
}

Suite *test_from_decimal_to_int() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("from_decimal_to_int");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_decimal_to_int_1);
  tcase_add_test(tc_core, test_decimal_to_int_2);
  tcase_add_test(tc_core, test_decimal_to_int_3);
  tcase_add_test(tc_core, test_decimal_to_int_4);
  suite_add_tcase(s, tc_core);

  return s;
}

Suite *test_from_decimal_to_float() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("from_decimal_to_float");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_decimal_to_float_1);
  tcase_add_test(tc_core, test_decimal_to_float_2);
  tcase_add_test(tc_core, test_decimal_to_float_3);
  tcase_add_test(tc_core, test_decimal_to_float_4);
  tcase_add_test(tc_core, test_decimal_to_float_5);
  suite_add_tcase(s, tc_core);

  return s;
}
