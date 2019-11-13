#include <stdlib.h>
#include <time.h>
#include <math.h>

// size of the window
#define WINDOW_DIM 400

// amount of energy the particles retain when hitting the walls
#define WALL_BOUNCINESS 0.2

// acceleration of the points towards sources of gravity
#define GRAVITY 0.005

// amount of momentum particles lose each frame
#define SPACE_DRAG 0.001

typedef struct {
    float x_pos;
    float y_pos;
    float x_momentum;
    float y_momentum;
} Particle;

Particle *create_particle(
    float x_pos,
    float y_pos,
    float x_momentum,
    float y_momentum
) {
    Particle *result = (Particle *) malloc(sizeof(Particle));
    result->x_pos = x_pos;
    result->y_pos = y_pos;
    result->x_momentum = x_momentum;
    result->y_momentum = y_momentum;
    return result;
}

void copy_particle(Particle *dest, Particle source) {
    dest->x_pos = source.x_pos;
    dest->y_pos = source.y_pos;
    dest->x_momentum = source.x_momentum;
    dest->y_momentum = source.y_momentum;
    return;
}

void free_particle(Particle *particle) {
    free(particle);
    return;
}

void update_particle(
    Particle *particle,
    int grav_x,
    int grav_y
) {
    particle->x_pos += particle->x_momentum;
    particle->y_pos += particle->y_momentum;

    particle->x_momentum *= (1.0 - SPACE_DRAG);
    particle->y_momentum *= (1.0 - SPACE_DRAG);

    if (particle->x_pos < 0) {
        particle->x_pos = 0;
        particle->x_momentum *= -WALL_BOUNCINESS; // lose a little energy
    }

    if (particle->x_pos > WINDOW_DIM) {
        particle->x_pos = WINDOW_DIM;
        particle->x_momentum *= -WALL_BOUNCINESS;
    }

    if (particle->y_pos < 0) {
        particle->y_pos = 0;
        particle->y_momentum *= -WALL_BOUNCINESS;
    }

    if (particle->y_pos > WINDOW_DIM) {
        particle->y_pos = WINDOW_DIM;
        particle->y_momentum *= -WALL_BOUNCINESS;
    }

    /* wherever the source of gravity is,
    things should accelerate towards it */
    if (particle->x_pos < grav_x) particle->x_momentum += GRAVITY;
    if (particle->x_pos > grav_x) particle->x_momentum -= GRAVITY;
    if (particle->y_pos < grav_y) particle->y_momentum += GRAVITY;
    if (particle->y_pos > grav_y) particle->y_momentum -= GRAVITY;
}

void collide(Particle *a, Particle b, int coinflip) {
    a->x_momentum = b.y_momentum;
    a->y_momentum = b.x_momentum;

    switch (coinflip) {
        case 0:
            a->x_pos -= 1;
            break;
        case 1:
            a->y_pos += 1;  
            break;
        case 2:
            a->x_pos += 1;
            break;
        case 3:
            a->y_pos -= 1;
            break;
    }
}
