/**
 * The structure of a Particle.
 */
typedef struct {
    float x_pos;
    float y_pos;
    float x_momentum;
    float y_momentum;
} Particle;


/**
 * Function to allocate a new Particle on the heap.
 * You must call free_particle() on the resultant Particle.
 *
 * @param x_pos the starting x-position of the Particle
 * @param y_pos the starting y-position of the Particle
 * @param x_momentum the starting x-momentum of the Particle
 * @param y_momentum the starting y-momentum of the Particle
 * @return pointer to the newly created Particle
 */
Particle *create_particle(
    float x_pos,
    float y_pos,
    float x_momentum,
    float y_momentum
);

/**
 * Function to copy the properties of one Particle to another.
 *
 * @param dest pointer to the Particle to be modified
 * @param source the Particle from which the data is to be copied
 */
void copy_particle(Particle *dest, Particle source);

/**
 * Function to free a heap-allocated Particle.
 *
 * @param particle pointer to the Particle to be freed
 */
void free_particle(Particle *particle);


/**
 * Function to update a particle's position.
 *
 * @param particle pointer to the Particle to update
 */
void update_particle(Particle *particle);
