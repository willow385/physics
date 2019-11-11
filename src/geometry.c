/* Functions for doing geometric calculations in C. */

#include <math.h>

#define CIRCLE_THICCNESS 1.0

int approx_eq(float a, float b) {
    if (fabs(a - b) < CIRCLE_THICCNESS) {
        return 1;
    }
    return 0;
}

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
    float points_dist = sqrt(
        pow((float)horiz_dist, 2.0)
        + pow((float)vert_dist, 2.0)
    );

    return approx_eq(points_dist, distance);
}
