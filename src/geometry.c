/* Functions for doing geometric calculations in C. */

#include <math.h>

int is_distance(
    int x_pos_0,
    int y_pos_0,
    int x_pos_1,
    int y_pos_1,
    float distance
) {
    // We will compute this with the pythagorean theorem.
    int horiz_dist = x_pos_1 - x_pos_0;
    int vert_dist = y_pos_1 - y_pos_0;
    float points_dist = (
        pow((float)horiz_dist, 2.0)
        + pow((float)vert_dist, 2.0)
    );

    return (points_dist <= sqrt(distance));
}
