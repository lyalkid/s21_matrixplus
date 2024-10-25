# корневой image образ для сборки - чистый ubuntu
FROM ubuntu

# обновляем apt пакеты и устанавливаем по очереди нужные зависимости
RUN apt-get update && apt-get install -y g++ make valgrind lcov clang-format vim libgtest-dev check

COPY . /code

# Устанавливаем
WORKDIR /code

CMD /bin/bash
