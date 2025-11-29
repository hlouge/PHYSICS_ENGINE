#include "physics.h"
#include <math.h>

#define g 9.81 // Gravité (positive car Y descend)

void gravity(Pointphysics* object, double dt, int width, int height) {
    // 1. MISE A JOUR HISTORIQUE (Indispensable pour la traînée !)
    for (int i = TRAIL_LENGTH - 1; i > 0; i--) {
        object->historyX[i] = object->historyX[i-1];
        object->historyY[i] = object->historyY[i-1];
    }
    object->historyX[0] = object->x;
    object->historyY[0] = object->y;

    // 2. PHYSIQUE (Vitesse et Position)
    object->vy += g * dt;       // Gravité
    object->x += object->vx * dt; // Vitesse X
    object->y += object->vy * dt; // Vitesse Y

    // 3. COLLISIONS

    // Sol (en bas, donc Y > height)
    if (object->y > height - 10) { 
        object->y = height - 10;
        object->vy = -object->vy * 0.7; // 0.7 = Perte d'énergie au rebond
    }

    // Mur de DROITE
    if (object->x > width - 10) {
        object->x = width - 10;
        object->vx = -object->vx * 0.7;
    } 
    // Mur de GAUCHE
    else if (object->x < 10) {
        object->x = 10;
        object->vx = -object->vx * 0.7;
    }
    // Mur du HAUT
    if (object->y < 10) {
        object->y = 10;
        object->vy = -object->vy * 0.7;
    }
}