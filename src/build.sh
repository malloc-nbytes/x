#!/bin/bash

set -xe

g++ -Iinclude/ -o main *.cpp include/templates/*.hpp
