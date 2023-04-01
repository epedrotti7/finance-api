#!/bin/bash

cd build
rm -rf *
cmake ..
make
./my_api_project
