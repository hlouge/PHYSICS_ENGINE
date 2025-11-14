#include <stdio.h>
#include <SDL2/SDL.h> // External dependency
#include "physics.h"  

#define DT 0.016 // for 60 Hz display

void draw_filled_circle(SDL_Renderer* renderer, int cx, int cy, int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}

int main (int argc, char* argv[]) {
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("SDL Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Physics Engine",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600, 0);

    if (!window) {
        printf("Rendering Window Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    // Creation of the Renderer 
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);
    
    if (!renderer) {
        printf("Renderer Creation Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    //Physical Object
    Pointphysics balle = { .x = 400, .y = 100, .vx = 0, .vy = 0 };
    
    printf("Simulation\n");

    const double dt = DT;

    int en_cours = 1;
    SDL_Event event;

    // Simulation
    while (en_cours) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                en_cours = 0;
            }
        }
        
        // Update Position
        gravity(&balle, 0.016);
        
        // Update Render 
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
        SDL_RenderClear(renderer); 
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        draw_filled_circle(renderer, (int)balle.x, (int)balle.y, 10);

        // Render the result on the screen
        SDL_RenderPresent(renderer);
                
        printf("Position: Y = %f\n", balle.y);

    }

    // Clear
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    printf("End of Sim.\n");
    return 0;
}