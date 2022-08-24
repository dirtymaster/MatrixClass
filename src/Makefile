CC+FLAGS = g++ -std=c++17 -Wall -Werror -Wextra
GCOVFLAGS = -L. --coverage -ls21_matrix_oop
OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lgtest -lm -pthread -lrt -lsubunit -g
else
	CHECK_FLAGS = -lgtest
endif

TEST_COMPILE = $(CC+FLAGS) tests.cpp s21_matrix_oop.a $(CHECK_FLAGS) -L. -ls21_matrix_oop

all: clean s21_matrix_oop.a test

clean:
	rm -rf *.o *.g* *.info *.out report *.a *.dSYM

rebuild: clean all

test: s21_matrix_oop.a
	$(TEST_COMPILE)
	./a.out

gcov_report: test
	rm -f *.g*
	$(CC+FLAGS) *.cpp $(CHECK_FLAGS) $(GCOVFLAGS)
	./a.out
	lcov -t a.out -o rep.info -c -d .
	genhtml -o report rep.info
	open ./report/index.html
	rm -rf *.gcda *.gcno *.info

s21_matrix_oop.a: s21_matrix_oop.o
	ar rcs libs21_matrix_oop.a *.o
	rm -rf *.o
	ranlib libs21_matrix_oop.a
	cp libs21_matrix_oop.a s21_matrix_oop.a
	cp libs21_matrix_oop.a ls21_matrix_oop.a

s21_matrix_oop.o:
	$(CC+FLAGS) -c s21*.cpp

lo:
	for i in `seq 100 $(OP)`;	do ./a.out; done;

check:
	python3 ../materials/linters/cpplint.py --extensions=c *.cpp *.h
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind ./a.out --leak-check=full
endif
	make clean
