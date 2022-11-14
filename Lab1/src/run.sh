#!/bin/zsh

set -e

Hostname="example.com"

make clean
make
./main ${Hostname} 