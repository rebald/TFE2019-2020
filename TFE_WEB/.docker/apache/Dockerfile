FROM debian:latest

RUN apt-get update -y \
    && apt-get -y install apache2

# Enable apache modules
RUN a2enmod rewrite headers \
    && a2enmod proxy_fcgi ssl
RUN echo "ServerName localhost" >> /etc/apache2/apache2.conf

WORKDIR /var/www
EXPOSE 80
COPY apache-foreground /usr/local/bin/
RUN chmod +x /usr/local/bin/apache-foreground

CMD ["apache-foreground"]
