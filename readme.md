# physics

Licensed under GNU GPL 3.0

This is a simple physics simulation. There is a red dot and a bunch of green dots.
The green dots accelerate towards the red dot as if by gravitational attraction.
They can collide with eachother, with the walls, and with the red dot.
You can move the red dot by dragging your cursor over the window.

A few months ago I wrote various SDL2-based programs, but they are very badly
written (look in my repository "djf-3d" to see what I mean). They are an embarassment.
I wrote this program to demonstrate that I know now how to do things the Right Way,
in pure C. C is what I am good at; whenever I write C++, I am really just writing C
with classes and iostreams. When I have attained true mastery of C, I will pick up C++
again, this time being sure to use the various features, data structures, and library
abstractions (vectors, smart pointers, RAII, etc.) that characterize modern C++. Since
I have not, in my own estimation, attained true mastery of C, I will not be writing C++
again for a good while.

You will need libsdl2-dev to make this program run. I have tested it on GNU/Linux and
MacOS X, and it seems to run fine on both platforms without the need to modify the source
code or the make script. However, my attempts to build and run it on Windows, with MinGW
or with Visual Studio, have failed. I therefore recommend that you run this on a Unix-like
operating system. Additionally, the make script is written in bash and relies on gcc.
