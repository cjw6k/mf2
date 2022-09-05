ARG PHP_VERSION="8.1-buster"

FROM php:${PHP_VERSION} as check-build-context
WORKDIR /usr/share/check-build-context
COPY . .
ENTRYPOINT ["/bin/bash"]

FROM php:${PHP_VERSION}

RUN apt-get update && apt-get install -y \
    libxml2-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/share/microformats
COPY *.* .

RUN phpize \
 && EXTRA_CFLAGS='-Wall -Wextra -Wno-unused-parameter' \
    ./configure \
 && make -j2 \
 && make install

RUN docker-php-ext-enable mf2

COPY tests tests

ENV REPORT_EXIT_STATUS=1
CMD ["php", "./run-tests.php", "-P", "-q", "--show-diff"]