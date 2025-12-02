#ifndef PHYSICS_H
#define PHYSICS_H

#define TRAIL_LENGTH 20

typedef struct {
    double initial_x;
    double initial_y;
    double initial_vx;
    double initial_vy;
    int radius;
    double gravity_val;
    int window_width;
    int window_height;
} Config;

typedef struct {
    double x, y;
    double vx, vy;
    double historyX[TRAIL_LENGTH];
    double historyY[TRAIL_LENGTH];
} Pointphysics;

void gravity(Pointphysics* object, double dt, int width, int height);

#endif  // PHYSICS_H