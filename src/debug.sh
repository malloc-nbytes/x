#!/bin/bash

set -xe

g++ -ggdb -O0 -Iinclude/ -o debug-build *.cpp include/templates/*.hpp
