#ifndef PHYSICS_H
#define PHYSICS_H

//struct for a physical object
typedef struct {
    double x, y;
    double vx, vy;
} Pointphysics;

void gravity(Pointphysics* object, double dt);


#endif //PHYSICS.h