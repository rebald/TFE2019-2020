until mysqladmin ping -h "database" --silent; do
  >&2 echo "Waiting for database..."
  sleep 1
done