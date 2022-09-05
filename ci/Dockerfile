ARG PHP_VERSION="8.1-buster"


###
### check-build-context
###
FROM php:${PHP_VERSION} as check-build-context

ARG EXA_VERSION=0.10.1

RUN apt-get update && apt-get install -y \
    unzip \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/share/exa
RUN curl -sLO https://github.com/ogham/exa/releases/download/v${EXA_VERSION}/exa-linux-x86_64-v${EXA_VERSION}.zip \
 && unzip exa-linux-x86_64-v${EXA_VERSION}.zip \
 && cp bin/exa /usr/local/bin/ \
 && cd .. \
 && rm exa -r

WORKDIR /usr/share/check-build-context

# TODO: is the required-for-good-ux-in-windows-10 chmod problematic?
COPY --chmod=0644 . .

ENTRYPOINT ["/usr/local/bin/exa"]
CMD ["--tree", "--level=10", "--icons", "--colour=always"]


###
### build
###
FROM php:${PHP_VERSION} as build

RUN apt-get update && apt-get install -y \
    libxml2-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/share/microformats
COPY *.* ./

RUN phpize \
 && EXTRA_CFLAGS='-Wall -Wextra -Wno-unused-parameter' \
    ./configure \
 && make -j2 \
 && make install

RUN docker-php-ext-enable mf2


###
### test
###
FROM build as test

COPY tests tests/

ENV REPORT_EXIT_STATUS=1
CMD ["php", "./run-tests.php", "-P", "-q", "--show-diff"]


###
### dev-build
###
FROM php:${PHP_VERSION} as dev-build

RUN apt-get update && apt-get install -y \
    libxml2-dev \
    gdb \
    valgrind

WORKDIR /usr/share/microformats
COPY *.* ./

RUN phpize \
 && EXTRA_CFLAGS='-Wall -Wextra -Wno-unused-parameter' \
    ./configure \
 && make -j2 \
 && make install

RUN docker-php-ext-enable mf2


###
### dev-test
###
FROM dev-build as dev-test
COPY tests tests/
CMD ["/bin/bash"]


###
### dev-valgrind
###
FROM dev-test as dev-valgrind

ENV ZEND_DONT_UNLOAD_MODULES=1
ENV USE_ZEND_ALLOC=0

CMD ["php", "./run-tests.php", "-m", "-P", "-q", "--show-diff"]

###
### dev-gdb
###
FROM dev-test as dev-gdb

ENV ZEND_DONT_UNLOAD_MODULES=1
ENV USE_ZEND_ALLOC=0

ENTRYPOINT ["gdb"]
CMD ["--args", "php", "-r", "echo PHP_EOL, ' -=-=-= hello, world! =-=-=-', PHP_EOL, PHP_EOL;"]
