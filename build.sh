#!/usr/bin/env bash

mkdir -p build
cd build
cmake -S ../ -B . -G "Unix Makefiles"
make
mv bmp_reader ../
cd ..