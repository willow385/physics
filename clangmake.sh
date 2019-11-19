#!/bin/bash
# This script will compile the program into a binary named "physics.x86".
# This script differs in that it uses Clang instead of clang.

cd src;
clang -c -O3 geometry.c;
clang -c -O3 particle.c;
cd ..;
clang  -O3 src/main.c\
       src/geometry.o\
       src/particle.o\
    -o physics.x86\
    -lm\
    `pkg-config --cflags --libs sdl2`;

