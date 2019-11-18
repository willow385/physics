/**
 * Function to tell if two points are a given distance apart.
 * @param horiz_dist the difference between the points' x-coords
 * @param vert_dist the difference between the points' y-coords
 * @param distance how far apart we want to know if they are
 * @return 1 if points are approximately [distance] pixels apart, else 0
 */
int is_distance(
    int horiz_dist,
    int vert_dist,
    float distance
);
