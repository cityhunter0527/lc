#!/bin/bash -x
g++ -std=c++11 -shared -o libBSTUtil.so -c -Wall -Werror -fpic BSTUtil.cpp
