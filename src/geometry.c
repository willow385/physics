/* Functions for doing geometric calculations in C. */

#include <math.h>

int is_distance(
    int horiz_dist,
    int vert_dist,
    float distance
) {
    // We will compute this with the pythagorean theorem.
    int points_dist = (
        pow(horiz_dist, 2)
        + pow(vert_dist, 2)
    );

    return (points_dist <= pow(distance, 2));
}
