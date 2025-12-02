#include "physics.h"
#include <math.h>

#define g 9.81 

void gravity(Pointphysics* object, double dt, int width, int height) {
    // Historic Update for the particle trail
    for (int i = TRAIL_LENGTH - 1; i > 0; i--) {
        object->historyX[i] = object->historyX[i-1];
        object->historyY[i] = object->historyY[i-1];
    }
    object->historyX[0] = object->x;
    object->historyY[0] = object->y;

    // Physics Update
    object->vy += g * dt;    
    object->x += object->vx * dt; 
    object->y += object->vy * dt; 

    // COLLISIONS
    // ground
    if (object->y > height - 10) { 
        object->y = height - 10;
        object->vy = -object->vy * 0.7;
    }

    // Right wall
    if (object->x > width - 10) {
        object->x = width - 10;
        object->vx = -object->vx * 0.7;
    } 
    // Left wall
    else if (object->x < 10) {
        object->x = 10;
        object->vx = -object->vx * 0.7;
    }
    // roof
    else if (object->y < 10) {
        object->y = 10;
        object->vy = -object->vy * 0.7;
    }
}