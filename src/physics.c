#include "physics.h"

#define g 9.81

void gravity(Pointphysics* object, double dt) {
    //Acceleration
    object->vy += g * dt;

    //update
    object->x += object->vx * dt;
    object->y += object->vy * dt;

    // Une simulation très simple de "rebond" sur le sol (à 600px)
    if (object->y > 600) {
        object->y = 600;
        object->vy = -object->vy * 0.8; // Perdre un peu d'énergie
    }
}
