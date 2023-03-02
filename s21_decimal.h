#ifndef _S21_DECIMAL_H_
#define _S21_DECIMAL_H_

#include <stdlib.h>

#define MASK_SCALE 0xff0000U
#define MASK_SIGN 1U << 31  // 0x80000000U

#define MAX_INT_SCALE 9
#define DEC_MAX_SCALE 28

#define TEN_POWER_NINE 1000000000U

#define _MAX_UINT_ 4294967295U

typedef struct {
  unsigned int bits[4];
} s21_decimal;

// Большой decimal
// Не содержит в себе служебной информации
// по типу знака и степени 10.
typedef struct {
  unsigned int part[6];
} big_decimal;

typedef union converter {
  int a;
  char b[3];
} un_scale;

#define ZERO_DECIMAL_A (x.bits[0] == 0 && x.bits[1] == 0 && x.bits[2] == 0)
#define ZERO_DECIMAL_B (y.bits[0] == 0 && y.bits[1] == 0 && y.bits[2] == 0)
#define DECIMAL_IS_ZERO(a) (a.bits[0] == 0 && a.bits[1] == 0 && a.bits[2] == 0)
// Функции возвращают код ошибки:
//  0 - OK
//  1 - число слишком велико или равно бесконечности
//  2 - число слишком мало или равно отрицательной бесконечности
//  3 - деление на 0

#define OK 0
#define INF_PLUS 1
#define INF_MINUS 2
#define DIV_BY_ZERO 3

// Сложение двух Decimal
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int summ_helper(big_decimal x, big_decimal y, big_decimal *z);

// Вычитание двух Decimal
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Умножение двух Decimal
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Деление двух Decimal
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Остаток от деления Mod
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Функции преобразования типов
#define CONVERSION_ERROR 1

// Из int в s21_decimal
int s21_from_int_to_decimal(int src, s21_decimal *dst);
// Из float в s21_decimal
int s21_from_float_to_decimal(float src, s21_decimal *dst);
// В int из s21_decimal
int s21_from_decimal_to_int(s21_decimal src, int *dst);
// В float из s21_decimal
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Фукнции сравнения
// Возвращаемые значения:
//  0 - False
//  1 - True

#define TRUE 1
#define FALSE 0

// Меньше <
int s21_is_less(s21_decimal x, s21_decimal y);
// Меньше или равно <=
int s21_is_less_or_equal(s21_decimal x, s21_decimal y);
// Больше >
int s21_is_greater(s21_decimal x, s21_decimal y);
// Больше или равно >=
int s21_is_greater_or_equal(s21_decimal x, s21_decimal y);
// Равно ==
int s21_is_equal(s21_decimal x, s21_decimal y);
// Не равно !=
int s21_is_not_equal(s21_decimal x, s21_decimal y);

// Другие функции
// Возвращаемое значение - код ошибки:
//  0 - OK
//  1 - ошибка вычисления
#define ERROR_ROUND 1

// Округляет указанное Decimal число до ближайшего целого числа в сторону
// отрицательной бесконечности.
int s21_floor(s21_decimal value, s21_decimal *result);
// Округляет Decimal до ближайшего целого числа.
int s21_round(s21_decimal value, s21_decimal *result);
// Возвращает целые цифры указанного Decimal числа; любые дробные цифры
// отбрасываются, включая конечные нули.
int s21_truncate(s21_decimal value, s21_decimal *result);
// Возвращает результат умножения указанного Decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result);

//==============================================
//
//           Второстепенные функции
//
//==============================================
void decimal_to_big_decimal(s21_decimal a, big_decimal *result);
void big_decimal_to_decimal(big_decimal result, unsigned int sign,
                            unsigned int scale, s21_decimal *a);

void bank_round(big_decimal *buffer, unsigned int *round_scale);
int add_uint(big_decimal *number, unsigned int a);
int div10_big_decimal(big_decimal *src, int scale, unsigned int *remainder,
                      unsigned int *last_remainder);
int div_big_decimal_on_uint(big_decimal *src, unsigned int divider,
                            unsigned int *last_remainder);

int mul10xbig_decimal(big_decimal *src, int scale);
unsigned long int mul_32x32_to_64(unsigned int a, unsigned int b);
void set_scale(s21_decimal *a, unsigned int scale);

//---------------------s21_sub---------------------------------
big_decimal aboba(big_decimal value_1, big_decimal value_2);
void preparing_numbers_for_subtraction(big_decimal *a, big_decimal *b,
                                       big_decimal *result);
int get_result_max_scale(int a, int b);
int get_result_min_scale(int a, int b);
int get_scale(s21_decimal a);
int get_bit(s21_decimal num, int number_of_int_in_array, int number_of_bits);
void set_bit(unsigned int *num, int number_of_bits, int bit);
int get_bit_big(big_decimal num, int number_of_int_in_array,
                int number_of_bits);

//---------------------s21_is_greater---------------------------
void help_in_scaling_values(s21_decimal a, s21_decimal b, big_decimal *big_a,
                            big_decimal *big_b, int *scale_a, int *scale_b);
int comparison(big_decimal a, big_decimal b,
               int flag);  // возвращает 1 если а>b, иначе 0
#endif  // _S21_DECIMAL_H_
