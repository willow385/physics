/**
 * Function to tell if two points are a given distance apart.
 * @param x_pos_0 the x-position of the first point
 * @param y_pos_0 the y-position of the first point
 * @param x_pos_1 the x-position of the second point
 * @param y_pos_1 the y-position of the second point
 * @param distance how far apart we want to know if they are
 * @return 1 if points are approximately [distance] pixels apart, else 0
 */
int is_distance(
    int x_pos_0,
    int y_pos_0,
    int x_pos_1,
    int y_pos_1,
    float distance
);
