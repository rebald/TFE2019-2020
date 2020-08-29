include .env

setup :
	$(call do_setup)

start-web :
	docker-compose up -d

ssh :
	docker exec -w /var/www -it api sh

migration :
	docker exec -w /var/www -it api sh -c 'php bin/console make:migration'

migrate :
	docker exec -w /var/www -it api sh -c 'php bin/console d:m:m'

define do_setup
	echo "Setting up ${APP}..."
	docker-compose up -d
	docker exec -w /var/www -it api sh -c 'composer install --prefer-dist --no-progress --no-suggest --optimize-autoloader'
	$(call do_db_healthcheck)
	docker exec -w /var/www -it api sh -c 'php bin/console d:d:d --if-exists --force'
	docker exec -w /var/www -it api sh -c 'php bin/console d:d:c --if-not-exists'
	docker exec -w /var/www -it api sh -c 'php bin/console d:m:m --no-interaction'
	docker exec -w /var/www -it api sh -c 'php bin/console d:f:l -q'
	docker exec -w /var/www -it api sh -c 'mkdir -p config/jwt'
	docker exec -w /var/www -it api sh -c 'openssl genpkey -out config/jwt/private.pem -aes256 -algorithm rsa -pkeyopt rsa_keygen_bits:4096'
	docker exec -w /var/www -it api sh -c 'openssl pkey -in config/jwt/private.pem -out config/jwt/public.pem -pubout'
	echo "\n"
	echo "${APP} setup complete"
endef

define do_db_healthcheck
	docker exec -it api sh -c 'chmod +x /var/www/docker/php/database-healthcheck.sh'
	docker exec -it api sh -c '/var/www/docker/php/database-healthcheck.sh'
endef
