TARGET = s21_matrix_oop.a
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lm -lstdc++
TEST_FLAGS = -lgtest -pthread

all: style cc test gcov_report 

$(TARGET): 
	mkdir obj/
	gcc $(CFLAGS) -c *.cpp 
	ar rc $(TARGET)  *.o 
	ranlib $(TARGET)  
	mv *.o obj/

style_test:
	clang-format --style=Google -n *.cpp *.h
style:
	clang-format --style=Google -i *.cpp *.h

cc:
	gcc $(CFLAGS) *.cpp -o matrix_cpp

test: clean $(TARGET)
	gcc $(CFLAGS) $(TEST_FLAGS) $(TARGET) tests/test.cpp -o matrix_test && ./matrix_test
	
clean:
	rm -rf matrix_cpp matrix_test $(TARGET) *.a obj/ *.out

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

