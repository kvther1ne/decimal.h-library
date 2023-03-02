#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int negative_value_1 = get_bit(value_1, 3, 31);
  int negative_value_2 = get_bit(value_2, 3, 31);
  int scale_value_1, scale_value_2, sign;
  unsigned round_scale;
  scale_value_1 = scale_value_2 = round_scale = sign = 0;
  big_decimal big_value_1 = {0};
  big_decimal big_value_2 = {0};
  big_decimal tmp = {0};

  // делаем числа положительными:
  set_bit(&value_1.bits[3], 31, 0);
  set_bit(&value_2.bits[3], 31, 0);

  // копируем децимал в биг децимал, приводим их к одному скейлу, получаем
  // значения изначальных скейлов:
  help_in_scaling_values(value_1, value_2, &big_value_1, &big_value_2,
                         &scale_value_1, &scale_value_2);

  if (negative_value_1 == 1 &&
      negative_value_2 == 0) {  // пример: - a - b = - (a + b); вызываем
                                // сложение под общим минусом
    int tmp = s21_add(value_1, value_2, result) ? 2 : 0;
    set_bit(&result->bits[3], 31, 1);
    return tmp;
  } else if (negative_value_1 == 0 &&
             negative_value_2 == 1) {  // пример:  a - (- b) = a + b; вызываем
                                       // сложение под общим плюсом
    int tmp = s21_add(value_1, value_2, result) ? 1 : 0;
    set_bit(&result->bits[3], 31, 0);
    return tmp;
  }

  // если вычитаемое больше, то присваиваем результату минус и меняем числа
  // местами

  if (s21_is_greater(value_1, value_2) == 0 && negative_value_1 == 0 &&
      negative_value_2 == 0) {
    sign = 1;
    tmp = aboba(big_value_2, big_value_1);
  } else if (s21_is_greater(value_1, value_2) == 1 && negative_value_1 == 0 &&
             negative_value_2 == 0) {
    sign = 0;
    tmp = aboba(big_value_1, big_value_2);
  }

  // если пришли оба отрицательных числа:

  if (negative_value_1 == 1 &&
      negative_value_2 == 1) {  // пример: - a - (- b) = b - a; результирующий
                                // знак определяется через сравнение чисел
    if (s21_is_greater(value_1, value_2) == 1) {
      sign = 1;
      tmp = aboba(big_value_1, big_value_2);
    } else {
      sign = 0;
      tmp = aboba(big_value_2, big_value_1);
    }
  }

  bank_round(&tmp,
             &round_scale);  // сводим биг децимал в децимал c округлением:

  round_scale = get_result_max_scale(scale_value_1, scale_value_2) -
                round_scale;  // получаем результирующий скейл

  big_decimal_to_decimal(
      tmp, sign, round_scale,
      result);  // заносим результаты знака, скейла и децимала в результат

  return 0;
}
