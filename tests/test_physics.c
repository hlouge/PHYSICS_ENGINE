#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "../src/physics.h"

// Helper pour comparer les doubles
int is_close(double a, double b) {
    return fabs(a - b) < 0.001;
}

void test_gravity() {
    // Test: Une particule doit tomber
    Pointphysics p = { .x=100, .y=100, .vx=0, .vy=0 };
    // Init historique (requis par votre code physics.c)
    for(int i=0; i<TRAIL_LENGTH; i++) { p.historyX[i]=0; p.historyY[i]=0; }

    gravity(&p, 1.0, 800, 600);

    // Après 1s, elle doit être descendue (y augmente) et avoir une vitesse positive
    assert(p.y > 100);
    assert(p.vy > 0);
    printf("[PASS] Gravity test\n");
}

void test_wall_bounce() {
    // Test: Une particule qui tape le mur de droite doit rebondir
    Pointphysics p = { .x=795, .y=100, .vx=100, .vy=0 }; // Juste avant le mur (800)
    for(int i=0; i<TRAIL_LENGTH; i++) { p.historyX[i]=0; p.historyY[i]=0; }

    // On simule une collision
    gravity(&p, 0.1, 800, 600);

    // La position doit être corrigée (<= 790) et vitesse inversée
    assert(p.x <= 790);
    assert(p.vx < 0);
    printf("[PASS] Wall bounce test\n");
}

int main() {
    test_gravity();
    test_wall_bounce();
    return 0;
}