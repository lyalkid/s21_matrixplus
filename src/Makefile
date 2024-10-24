TARGET = s21_matrix_oop.a
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lm -lstdc++ 
TEST_FLAGS = -pthread -lgtest 
SOURCE = $(wildcard *.cpp)
TESTS_SOURCE = $(wildcard tests/*.cpp)
all: style cc test gcov_report 



ifeq ($(UNAME_S),Linux)
  	OPEN_CMD = firefox
	ADD_LIB = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
endif
ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
	ADD_LIB =
endif

$(TARGET): style
	mkdir obj/
	gcc $(CFLAGS) -c *.cpp 
	ar rc $(TARGET)  *.o 
	ranlib $(TARGET)  
	mv *.o obj/

style_test:
	clang-format --style=Google -n *.cpp  tests/*.cpp *.h
style:
	clang-format --style=Google -i *.cpp  tests/*.cpp *.h

cc:
	gcc $(CFLAGS) *.cpp -o matrix_cpp

test: clean $(TARGET)
	gcc $(CFLAGS) $(TEST_FLAGS) $(TARGET) tests/test.cpp -o matrix_test && ./matrix_test
	
failed_test: clean $(TARGET)
	gcc $(CFLAGS) $(TEST_FLAGS) $(TARGET) tests/test.cpp -o matrix_test && ./matrix_test | grep "FAILED"

clean:
	rm -rf matrix_cpp matrix_test $(TARGET) *.a obj/ *.out  *.o gcovr  *.dSYM 


gcov_report: clean 
	mkdir gcovr
	gcc --coverage $(CFLAGS) $(TEST_FLAGS) $(SOURCE) tests/test.cpp -o ./gcovr/gtest_test
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

