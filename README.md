# decimal.h-library

## Implementation of my own s21_decimal.h library in C

In this project our team implemented the s21_decimal.h library in the C programming language. This library add the ability to work with the "decimal" type, which is not in the language standard. This type is critically important for financial calculations, for example, where errors of calculations characteristic of types with floating point are unacceptable. As part of the project we worked with the tasks of processing financial information, dive into the issues of internal representation of different types of data, and solidify knowledge of structured programming.

The binary representation of a Decimal number consists of a 1-bit sign, a 96-bit integer number, and a scaling factor used to divide the integer number and specify what portion of it is a decimal fraction. The scaling factor is implicitly the number 10, raised to an exponent ranging from 0 to 28.
Decimal number can be implemented as a four-element array of 32-bit signed integers (int bits[4];).
bits[0], bits[1], and bits[2] contain the low, middle, and high 32 bits of the 96-bit integer number accordingly.
bits[3] contains the scale factor and sign, and consists of following parts:

- Bits 0 to 15, the lower word, are unused and must be zero.
- Bits 16 to 23 must contain an exponent between 0 and 28, which indicates the power of 10 to divide the integer number.
- Bits 24 to 30 are unused and must be zero.
- Bit 31 contains the sign; 0 meaning positive, and 1 meaning negative.

### Arithmetic operators

| Operator name       | Operators        | Function            |
| ------------- |:------------------:|:----------------------:|
| Addition    |  +   | int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |
| Substraction   | - | int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) |
| Multiplication | * |
| Division  | /  |
| Modulo  | mod |
