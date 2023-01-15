set -e

make Client_main
rm -rf ./ClientData/*
./bin/Client_main < Client_cmd.txt