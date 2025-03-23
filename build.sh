#!/usr/bin/env bash

set -e
set -x

cmake -S . -B ./build
cmake --build ./build
cp build/libgdclips.so demo/bin/