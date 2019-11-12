#include <stdlib.h>
#include <time.h>
#include <math.h>

#define WINDOW_DIM 400

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

    if (particle->x_pos < 0) {
        particle->x_pos = 0;
        particle->x_pos *= -1;
    }

    if (particle->x_pos > WINDOW_DIM) {
        particle->x_pos = WINDOW_DIM;
        particle->x_pos *= -1;
    }

    if (particle->y_pos < 0) {
        particle->y_pos = 0;
        particle->y_pos *= -1;
    }

    if (particle->y_pos > WINDOW_DIM) {
        particle->y_pos = WINDOW_DIM;
        particle->y_pos *= -1;
    }


    if (particle->x_pos < grav_x) particle->x_momentum += 1;
    if (particle->x_pos > grav_x) particle->x_momentum -= 1;
    if (particle->y_pos < grav_y) particle->y_momentum += 1;
    if (particle->y_pos > grav_y) particle->y_momentum -= 1;
}

void collide(Particle *a, Particle *b) {
    srand(time(NULL));

    float a_orig_x_m = a->x_momentum;
    float a_orig_y_m = a->y_momentum;
    float b_orig_x_m = b->y_momentum;
    float b_orig_y_m = b->y_momentum;

    a->x_momentum = b_orig_y_m;
    a->y_momentum = b_orig_x_m;
    b->x_momentum = a_orig_y_m;
    b->y_momentum = a_orig_x_m;
}
