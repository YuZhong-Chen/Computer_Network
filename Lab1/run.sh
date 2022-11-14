#!/bin/bash

set -e

URL="can.cs.nthu.edu.tw/index.php"

make clean
make
./bin/main ${URL} 
