style_test:
	clang-format --style=Google -n *.cpp *.h
style:
	clang-format --style=Google -i *.cpp *.h

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

