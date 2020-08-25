FROM php:fpm-alpine

COPY --from=composer /usr/bin/composer /usr/bin/composer

RUN pecl install xdebug apcu; \
    docker-php-ext-install pdo_mysql; \
    docker-php-ext-enable xdebug apcu; \
    pecl clear-cache; \
    apk add mariadb-client;