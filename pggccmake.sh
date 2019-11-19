#!/bin/bash
# This script will compile the program into a binary named "physics.x86" and prepare
# it for profiling with gprof.

cd src;
gcc -pg -c geometry.c -lm;
gcc -pg -c particle.c;
cd ..;
gcc -pg src/main.c\
       src/geometry.o\
       src/particle.o\
    -o physics.x86\
    -lm\
    `pkg-config --cflags --libs sdl2`;

