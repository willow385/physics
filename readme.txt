physics - a personal project of {Dante,Claire} Falzone

Licensed under GNU GPL 3.0

This is a simple physics simulation showing a bunch of particles
that respond to movements of the mouse. I wrote it entirely in C
both to demonstrate that I could do so and to demonstrate that I
now know how to do it the Right Way (with headerfiles and a Make
file, etc). For comparison see my project "djf-3d", whose URL is
https://github.com/DanteFalzone0/djf-3d, where everything is all
done in very much Not The Right Way.

Run `make` to compile the program normally; this produces a file
called `physics.x86` which is executable. Some other make rules:

    run - run the program.
    debug - compile with debugging symbols for gdb.
    asm - compile into Assembly for you to read if you want to.
    clean - remove the executable and object files from /src/.
    prof - make a program that will output gmon.out for gprof.
    clean-prof - remove both the executable and gmon.out.
    clean-asm - remove Assembly files, if present, from /src/.

See also https://github.com/DanteFalzone0/physics-rs.
