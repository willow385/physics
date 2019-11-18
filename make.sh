#!/bin/bash
# This script will compile the program into a binary named "physics.x86".

cd src;
gcc -c geometry.c -lm;
gcc -c particle.c;
cd ..;
gcc  src/main.c\
       src/geometry.o\
       src/particle.o\
    -o physics.x86\
    -lm\
    `pkg-config --cflags --libs sdl2`;

