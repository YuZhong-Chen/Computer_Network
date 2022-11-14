#!/bin/bash

set -e

Hostname="example.com"

make clean
make
./main ${Hostname} 
