#!/bin/bash
# This script will compile the program into a binary named "physics.x86".

cd src;
gcc -c -O3 geometry.c -lm;
gcc -c -O3 particle.c;
cd ..;
gcc -O3 src/main.c\
       src/geometry.o\
       src/particle.o\
    -o physics.x86\
    -lm\
    `pkg-config --cflags --libs sdl2`;

