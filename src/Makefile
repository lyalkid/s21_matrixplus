TARGET = s21_matrix_oop.a
CFLAGS = -Wall -Werror -Wextra -std=c++17 -pedantic -lm -lstdc++
TEST_FLAGS = -pthread -lgtest 
SOURCE = $(wildcard *.cpp)
TESTS_SOURCE = $(wildcard tests/*.cpp)
CC = g++
UNAME_S = $(bash uname -s)

all: style test gcov_report 

ifeq ($(bash uname -s),Linux)
	CC = g++
  	OPEN_CMD = firefox
	TEST_FLAGS = -I/usr/local/include -L/usr/local/lib -lgtest -lgtest_main -pthread #-lsubunit
endif
ifeq ($(shell uname -s),Darwin)
	OPEN_CMD = open
	TEST_FLAGS = -pthread -lgtest -lm -lstdc++
endif

$(TARGET): 
	$(CC) $(CFLAGS) -c *.cpp 
	ar rc $(TARGET)  *.o 
	ranlib $(TARGET)  


style_test:
	clang-format --style=Google -n *.cpp  tests/*.cpp *.h
style:
	clang-format --style=Google -i *.cpp  tests/*.cpp *.h


test: clean $(TARGET)
	$(CC) $(CFLAGS)  tests/test.cpp  $(TARGET) $(TEST_FLAGS) -o matrix_test && ./matrix_test 
	
failed_test: clean $(TARGET)
	$(CC) $(CFLAGS)  tests/test.cpp  $(TARGET) $(TEST_FLAGS) -o matrix_test && ./matrix_test | grep "FAILED"

clean:
	rm -rf matrix_cpp matrix_test $(TARGET) *.a obj/ *.out  *.o gcovr  *.dSYM 

valg: clean test
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./matrix_test

valgrind: clean test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=leaks_log.txt ./matrix_test
	echo --- Valgrind summary --- && cat leaks_log.txt | grep 'total heap usage' && cat leaks_log.txt | grep 'ERROR SUMMARY'

gcov_report: clean 
	mkdir gcovr
	$(CC) --coverage $(CFLAGS) $(TEST_FLAGS) $(SOURCE) tests/test.cpp -o ./gcovr/gtest_test
	chmod +x ./gcovr/gtest_test
	./gcovr/gtest_test
	lcov --capture --branch-coverage --directory . --output-file ./gcovr/coverage.info --no-external --ignore-errors inconsistent,inconsistent
	lcov --list ./gcovr/coverage.info
	genhtml ./gcovr/coverage.info --output-directory ./gcovr/coverage_report
	open ./gcovr/coverage_report/index.html

# Собираем docker image с тегом 'v1' на основании dockerfile и создаем контейнер
docker_build:
	docker build -t vault:v1 .
	docker create -it --name matrix_cpp vault:v1

# Запускаем контейнер
docker_start:
	docker start -i matrix_cpp

docker_delete:
	docker rm matrix_cpp
	docker image rm vault:v1

