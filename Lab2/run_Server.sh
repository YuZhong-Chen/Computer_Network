set -e

PORT="9999"

make Server_main
./bin/Server_main ${PORT} 