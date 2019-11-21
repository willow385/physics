# specify your own C compiler if you don't have gcc
CC = gcc


# flags (may be gcc-specific)
FLAGS = -O3 -Wall


# debug flags (if you want a debuggable version)
DEBUG = -g -Wall


# asm flags (if you want to read the assembly output)
ASM = -S\
      -fverbose-asm\
      -masm=intel\
      -fno-asynchronous-unwind-tables\
      -Wall


# flags for gprof
PROF = -pg -Wall


# flags for linking SDL2
SDL2 = -D_REENTRANT -I/usr/include/SDL2 -lSDL2


# name of the target
TARGET = physics.x86


# required sourcefiles
SOURCE = src/geometry.c\
	 src/geometry.h\
	 src/main.c\
	 src/particle.c\
	 src/particle.h


# expected object files for main.c
OBJS = src/geometry.o src/particle.o


$(TARGET): $(SOURCE)
	$(CC) $(FLAGS) -c src/geometry.c -o src/geometry.o -lm
	$(CC) $(FLAGS) -c src/particle.c -o src/particle.o
	$(CC) $(FLAGS) $(OBJS) src/main.c -o $(TARGET) $(SDL2) -lm

run: $(TARGET)
	./$(TARGET)

prof: $(SOURCE)
	$(CC) $(PROF) -c src/geometry.c -o src/geometry.o -lm
	$(CC) $(PROF) -c src/particle.c -o src/particle.o
	$(CC) $(PROF) $(OBJS) src/main.c -o $(TARGET) $(SDL2) -lm

asm: $(SOURCE)
	$(CC) $(ASM) -c src/geometry.c -o src/geometry.s
	$(CC) $(ASM) -c src/particle.c -o src/particle.s
	$(CC) $(ASM) src/main.c -o src/main.s

debug: $(SOURCE)
	$(CC) $(DEBUG) -c src/geometry.c -o src/geometry.o -lm
	$(CC) $(DEBUG) -c src/particle.c -o src/particle.o
	$(CC) $(DEBUG) $(OBJS) src/main.c -o $(TARGET) $(SDL2) -lm


clean: $(TARGET) $(OBJS)
	rm $(TARGET)
	rm $(OBJS)

clean-asm: src/geometry.s src/main.s src/particle.s
	rm src/geometry.s src/main.s src/particle.s

clean-prof: gmon.out $(TARGET)
	rm gmon.out $(TARGET)
