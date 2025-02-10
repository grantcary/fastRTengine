#!/bin/bash

cd src
clang render.c camera.c object.c ray.c vmath.c vops.c -lm
echo "compiled!"
echo "running..."
./a.out
cd ../utils
python3 data2image.py
echo "displaying..."