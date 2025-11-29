#include <stdio.h>
#include <SDL2/SDL.h> 
#include "physics.h"  
#include <string.h> 
#include <stdlib.h> 
#include <time.h>

#define DT 0.016 // for 60 Hz display
#define NB_PARTICLES 150 // Nombre de particules

void draw_filled_circle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}

Config load_config(const char* filename) {
    Config conf = { .initial_x = 400, .initial_y = 100, .initial_vx = 0, .initial_vy = 0, .radius = 10, .gravity_val = 9.81 };
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Attention: Config introuvable.\n");
        return conf;
    }
    char key[64];
    while (fscanf(file, "%63s", key) == 1) {
        if (strcmp(key, "POS_X") == 0) fscanf(file, "%lf", &conf.initial_x);
        else if (strcmp(key, "POS_Y") == 0) fscanf(file, "%lf", &conf.initial_y);
        else if (strcmp(key, "VEL_X") == 0) fscanf(file, "%lf", &conf.initial_vx);
        else if (strcmp(key, "VEL_Y") == 0) fscanf(file, "%lf", &conf.initial_vy);
        else if (strcmp(key, "RADIUS") == 0) fscanf(file, "%d", &conf.radius);
        else if (strcmp(key, "GRAVITY") == 0) fscanf(file, "%lf", &conf.gravity_val);
        else if (strcmp(key, "WIN_W") == 0) fscanf(file, "%d", &conf.window_width);
        else if (strcmp(key, "WIN_H") == 0) fscanf(file, "%d", &conf.window_height);
    }
    fclose(file);
    return conf;
}

int main (int argc, char* argv[]) {
    Config conf = load_config("config.txt");

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return 1;

    SDL_Window* window = SDL_CreateWindow("Feu d'Artifice Physics",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          conf.window_width, conf.window_height, 0);
    if (!window) return 1;
    
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // Important pour la transparence
    
    if (!renderer) return 1;
    
    printf("Simulation Feu d'Artifice demarree...\n");

    const double dt = DT;
    int en_cours = 1;
    SDL_Event event;

    srand(time(NULL)); 

    // --- INITIALISATION DU TABLEAU DE PARTICULES ---
    Pointphysics particles[NB_PARTICLES];
    
    for(int i=0; i<NB_PARTICLES; i++) {
        particles[i].x = 400; // Centre X
        particles[i].y = 300; // Centre Y
        
        // Vitesse aléatoire (Explosion)
        particles[i].vx = (rand() % 400 - 200) * 2.0; 
        particles[i].vy = (rand() % 400 - 200) * 2.0;

        // Historique à zéro
        for(int h=0; h<TRAIL_LENGTH; h++) {
            particles[i].historyX[h] = 400;
            particles[i].historyY[h] = 300;
        }
    }

    // --- BOUCLE PRINCIPALE ---
    while (en_cours) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) en_cours = 0;
            
            // Relancer l'explosion avec Espace
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                for(int i=0; i<NB_PARTICLES; i++) {
                    particles[i].x = 400; 
                    particles[i].y = 300; 
                    particles[i].vx = (rand() % 400 - 200) * 2.0; 
                    particles[i].vy = (rand() % 400 - 200) * 2.0;
                }
            }
        }
        
        // 1. NETTOYER L'ECRAN
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255); // Fond gris très foncé
        SDL_RenderClear(renderer); 

        // 2. BOUCLE SUR TOUTES LES PARTICULES
        for (int p = 0; p < NB_PARTICLES; p++) {
            
            // A. Update Physique
            gravity(&particles[p], dt, conf.window_width, conf.window_height);

            // Générer une couleur unique basée sur l'index 'p' (pour faire joli)
            int r_col = (p * 50) % 256;
            int g_col = (p * 80) % 256;
            int b_col = (p * 110) % 256;

            // B. Dessiner la TRAÎNÉE
            for (int i = 0; i < TRAIL_LENGTH; i++) {
                int alpha = 200 - (i * (200 / TRAIL_LENGTH));
                if (alpha < 0) alpha = 0;

                SDL_SetRenderDrawColor(renderer, r_col, g_col, b_col, alpha);
                
                // Rayon plus petit pour les particules (3px max)
                int r = 4 - (i * 4 / TRAIL_LENGTH); 
                if (r > 0) {
                    draw_filled_circle(renderer, (int)particles[p].historyX[i], (int)particles[p].historyY[i], r);
                }
            }

            // C. Dessiner la TÊTE de la particule
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Tête blanche brillante
            draw_filled_circle(renderer, (int)particles[p].x, (int)particles[p].y, 4);
        }

        // 3. AFFICHER LE RESULTAT
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}