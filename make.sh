#!/bin/bash
# This script will compile the program into a binary named "physics.x86".

cd src;
gcc -g -c geometry.c -lm;
gcc -g -c particle.c;
cd ..;
gcc -g src/main.c\
       src/geometry.o\
       src/particle.o\
    -o physics.x86\
    -lm\
    `pkg-config --cflags --libs sdl2`;

