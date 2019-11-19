#!/bin/bash
# This script will compile the program into a binary named "physics.x86".
# This script differs in that it uses Clang instead of clang.
# This is for use with gprof.

cd src;
clang -c -pg geometry.c;
clang -c -pg particle.c;
cd ..;
clang  src/main.c\
       src/geometry.o\
       src/particle.o\
    -o physics.x86\
    -lm\
    -pg\
    `pkg-config --cflags --libs sdl2`;

