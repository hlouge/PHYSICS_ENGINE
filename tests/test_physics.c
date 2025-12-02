#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "../src/physics.h" // On inclut le header de votre projet

// Helper pour comparer des doubles (à cause des imprécisions flottantes)
int is_close(double a, double b) {
    return fabs(a - b) < 0.001;
}

void test_gravity_fall() {
    printf("[TEST] Gravity Fall... ");
    // Setup : Une particule immobile au milieu
    Pointphysics p = { .x=100, .y=100, .vx=0, .vy=0 };
    // Init de l'historique pour éviter les erreurs
    for(int i=0; i<TRAIL_LENGTH; i++) p.historyY[i] = 0;

    // Action : 1 seconde de simulation
    gravity(&p, 1.0, 800, 600);

    // Assert : Elle doit être descendue (y augmente) et avoir gagné de la vitesse Y
    assert(p.y > 100);
    assert(p.vy > 0); 
    // Avec g=9.81 et dt=1.0, vy devrait être ~9.81
    assert(is_close(p.vy, 9.81));
    
    printf("PASSED\n");
}

void test_floor_collision() {
    printf("[TEST] Floor Collision... ");
    int height = 600;
    // Setup : Une particule qui dépasse le sol (y=650) avec une vitesse vers le bas
    Pointphysics p = { .x=100, .y=650, .vx=0, .vy=100 };
    for(int i=0; i<TRAIL_LENGTH; i++) p.historyY[i] = 0;

    // Action
    gravity(&p, 0.1, 800, height);

    // Assert : 
    // 1. La position doit être corrigée au niveau du sol (height - 10)
    assert(is_close(p.y, height - 10));
    // 2. La vitesse doit être inversée (négative) et réduite (x 0.7)
    assert(p.vy < 0);
    // Vitesse attendue : (100 + 9.81*0.1) * -0.7 = -70.xxx
    
    printf("PASSED\n");
}

void test_wall_collision() {
    printf("[TEST] Wall Collision... ");
    int width = 800;
    // Setup : Une particule qui dépasse le mur de droite
    Pointphysics p = { .x=850, .y=100, .vx=100, .vy=0 };
    for(int i=0; i<TRAIL_LENGTH; i++) p.historyX[i] = 0;

    gravity(&p, 0.1, width, 600);

    // Assert : Position corrigée et vitesse inversée
    assert(is_close(p.x, width - 10));
    assert(p.vx < 0);

    printf("PASSED\n");
}

int main() {
    printf("=== RUNNING UNIT TESTS ===\n");
    test_gravity_fall();
    test_floor_collision();
    test_wall_collision();
    printf("=== ALL TESTS PASSED ===\n");
    return 0;
}