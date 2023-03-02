# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --trace-children=yes --track-fds=yes --log-file=valgrind.log ./test
CFLAGS=-Wall -Wextra -std=c11# -O2
SOURCES=dec_converts.c secondary_functions.c s21_mul.c\
		dec_rounds.c s21_sub.c s21_is_greater.c s21_is_equal.c s21_is_less_or_equal.c\
		s21_is_greater_or_equal.c s21_is_less.c s21_is_not_equal.c\
		s21_add.c s21_div.c secondary_functions_division.c s21_mod.c
OBJECTS=$(SOURCES:.c=.o)
TEST_SOURCE=tests/test_convert.c tests/test_equal.c tests/test_mul.c\
		tests/test.c tests/test_round.c tests/test_sub.c tests/test_greater.c\
		tests/test_less_or_equal.c tests/test_greater_or_equal.c\
		tests/test_less.c tests/test_not_equal.c tests/test_add.c tests/test_div.c tests/test_mod.c


UNAME = $(shell uname -s)
FLAGS = 

ifeq ($(UNAME), Linux)
	FLAGS += -lcheck_pic -lm -lsubunit -lrt -lpthread
else
	FLAGS += -lcheck -lm
endif

all: clean s21_decimal.a test

deb: clean s21_decimal.a
	gcc $(CFLAGS) dec_debug.c s21_decimal.a -o debug
	./debug

#=============Lib============
s21_decimal.a: $(OBJECTS)
	ar rc s21_decimal.a $(OBJECTS)
	ranlib s21_decimal.a
	rm -f  *.o

secondary_functions.o:
	gcc $(CFLAGS) -lm -c secondary_functions.c

dec_converts.o:
	gcc $(CFLAGS) -lm -c dec_converts.c

dec_scale.o:
	gcc $(CFLAGS) -lm -c dec_scale.c

dec_mul.o:
	gcc $(CFLAGS) -lm -c dec_mul.c

dec_rounds.o:
	gcc $(CFLAGS) -lm -c dec_rounds.c

s21_sub.o:
	gcc $(CFLAGS) -lm -c s21_sub.c

s21_add.o:
	gcc $(CFLAGS) -lm -c s21_add.c

s21_is_greater.o:
	gcc $(CFLAGS) -lm -c s21_is_greater.c
	
s21_is_equal.o:
	gcc $(CFLAGS) -lm -c s21_is_equal.c

s21_is_less_or_equal.o:
	gcc $(CFLAGS) -lm -c s21_is_less_or_equal.c

s21_is_greater_or_equal.o:
	gcc $(CFLAGS) -lm -c s21_is_greater_or_equal.c

s21_is_less.o:
	gcc $(CFLAGS) -lm -c s21_is_less.c

s21_is_not_equal.o:
	gcc $(CFLAGS) -lm -c s21_is_not_equal.c

s21_div.o:
	gcc $(CFLAGS) -lm -c s21_div.c

s21_mod.o:
	gcc $(CFLAGS) -lm -c s21_mod.c

secondary_functions_division.o:
	gcc $(CFLAGS) -lm -c secondary_functions_division.c

#============Test============
test: clean s21_decimal.a
	gcc $(TEST_SOURCE) $(CFLAGS) $(FLAGS) s21_decimal.a -o test -lcheck
	./test

#==========Valgrind==========

valgrind: clean s21_decimal.a
	gcc $(TEST_SOURCE) $(CFLAGS) $(FLAGS) s21_decimal.a -o test -lcheck
	valgrind --leak-check=full --track-fds=yes --log-file=valgrind.log ./test
	grep ERROR valgrind.log

#=========gcov_report========
gcov_report: clean
	gcc -lm --coverage -O0 -c $(SOURCES)
	ar rc s21_decimal.a $(OBJECTS)
	ranlib s21_decimal.a
	gcc --coverage -lcheck -lm $(TEST_SOURCE) s21_decimal.a -o test
	rm -f  *.o
	./test
	lcov -t "s21_test" -o s21_test.info -c -q -d .
	genhtml -o report s21_test.info
	rm -f *.gc* *.info
	open report/index.html

#============Clean===========
clean:
	rm -rf *.o *.a debug* test a.out *.gc* *.info report valgrind.log