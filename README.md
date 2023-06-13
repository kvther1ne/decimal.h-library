# decimal.h-library

## Реализация библиотеки decimal.h на языке C

В этом проекте наша команда реализовала библиотеку s21_decimal.h на языке программирования Си. Эта библиотека добавляет возможность работы с типом "decimal", который отсутствует в стандарте языка. Тем не менее, этот тип критически важен для, например, финансовых расчетов, где недопустимы погрешности вычислений, свойственные типам с плавающей точкой. В рамках этого проекта предполагается знакомство с задачами обработки финансовой информации, погружение в вопросы внутреннего представления различных типов данных и закрепление структурного подхода.

Тип Decimal представляет десятичные числа в диапазоне от положительных 79,228,162,514,264,337,593,543,950,335 до отрицательных 79,228,162,514,264,337,593,543,950,335. Значение Decimal по умолчанию равно 0. Decimal подходит для финансовых расчетов, которые требуют большого количества значимых целых и дробных цифр и отсутствия ошибок округления. Этот тип не устраняет необходимость округления. Скорее, сводит к минимуму количество ошибок из-за округления.
Decimal число - это значение с плавающей точкой, состоящее из знака, числового значения, где каждая цифра находится в диапазоне от 0 до 9, и коэффициента масштабирования, который указывает положение десятичной точки, разделяющей целые и дробные части числового значения.
Двоичное представление Decimal состоит из 1-разрядного знака, 96-разрядного целого числа и коэффициента масштабирования, используемого для деления 96-разрядного целого числа и указания того, какая его часть является десятичной дробью. Коэффициент масштабирования неявно равен числу 10, возведенному в степень в диапазоне от 0 до 28. Следовательно, двоичное представление Decimal имеет вид ((от -2^96 до 2^96) / 10^(от 0 до 28)), где -(2^96-1) равно минимальному значению, а 2^96-1 равно максимальному значению.
Двоичное представление Decimal состоит из 1-разрядного знака, 96-разрядного целого числа и коэффициента масштабирования, используемого для деления целого числа и указания того, какая его часть является десятичной дробью. Коэффициент масштабирования неявно равен числу 10, возведенному в степень в диапазоне от 0 до 28.
Decimal число может быть реализовано в виде четырехэлементного массива 32-разрядных целых чисел со знаком (int bits[4];).
bits[0], bits[1], и bits[2] содержат младшие, средние и старшие 32 бита 96-разрядного целого числа соответственно.
bits[3] содержит коэффициент масштабирования и знак, и состоит из следующих частей:

- Биты от 0 до 15, младшее слово, не используются и должны быть равны нулю.
- Биты с 16 по 23 должны содержать показатель степени от 0 до 28, который указывает степень 10 для разделения целого числа.
- Биты с 24 по 30 не используются и должны быть равны нулю.
- Бит 31 содержит знак; 0 означает положительный, а 1 означает отрицательный.

### Арифметические операции

| Operator name       | Operators        | Function            |
| ------------- |:------------------:|:----------------------:|
| Addition    |  +   | int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |
| Substraction   | - | int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |
| Multiplication | * | int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |
| Division  | /  | int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |
| Modulo  | mod | int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |

The functions return the error code:

- 0 - OK
- 1 - the number is too large or equal to infinity
- 2 - the number is too small or equal to negative infinity
- 3 - division by 0

Note on the numbers that do not fit into the mantissa:

- When getting numbers that do not fit into the mantissa during arithmetic operations, use bank rounding (for example, 79,228,162,514,264,337,593,543,950,335 - 0.6 = 79,228,162,514,264,337,593,543,950,334)

Note on the mod operation:

- If an overflow occurred as a result, discard the fractional part (for example, 70,000,000,000,000,000,000,000,000,000 % 0.001 = 0.000)

### Comparison Operators

| Operator name       | Operators        | Function            |
| ------------- |:------------------:|:----------------------:|
| Less than    |  <  | int s21_is_less(s21_decimal, s21_decimal) |
| Less than or equal to   | <= | int s21_is_less_or_equal(s21_decimal, s21_decimal) |
| Greater than | > | int s21_is_greater(s21_decimal, s21_decimal) |
| Greater than or equal to  | >=  | int s21_is_greater_or_equal(s21_decimal, s21_decimal) |
| Equal to  | == | int s21_is_equal(s21_decimal, s21_decimal) |
| Not equal to  | != | int s21_is_not_equal(s21_decimal, s21_decimal) |

Return value:

- 0 - FALSE
- 1 - TRUE

### Convertors and parsers

| Convertor/Parser       |  Function            |
| ------------- |:------------------:|
| From int   |  int s21_from_int_to_decimal(int src, s21_decimal *dst)  |
| From float   | int s21_from_float_to_decimal(float src, s21_decimal *dst) |
| To int |  int s21_from_decimal_to_int(s21_decimal src, int *dst) |
| To float  | int s21_from_decimal_to_float(s21_decimal src, float *dst)  |

Return value - code error:

- 0 - OK
- 1 - convertation error

Note on the conversion of a float type number:

- If the numbers are too small (0 < |x| < 1e-28), return an error and value equal to 0
- If the numbers are too large (|x| > 79,228,162,514,264,337,593,543,950,335) or are equal to infinity, return an error
- When processing a number with the float type, convert all the significant decimal digits contained in it. If there are more than 7 such digits, the number is rounded to the closest one that does not have more than 7 significant decimal digits.

Note on the conversion from decimal type to int:

- If there is a fractional part in a decimal number, it should be discarded (for example, 0.9 is converted to 0)

### Another functions

| Description       |  Function            |
| ------------- |:------------------:|
| Rounds a specified Decimal number to the closest integer toward negative infinity.   |  int s21_floor(s21_decimal value, s21_decimal *result)  |
| Rounds a decimal value to the nearest integer.   | int s21_round(s21_decimal value, s21_decimal *result) |
| Returns the integral digits of the specified Decimal; any fractional digits are discarded, including trailing zeroes. |  int s21_truncate(s21_decimal value, s21_decimal *result) |
| Returns the result of multiplying the specified Decimal value by negative one.  | int s21_negate(s21_decimal value, s21_decimal *result)  |

Return value - code error:

- 0 - OK
- 1 - calculation error
