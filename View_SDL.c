#include <stdio.h>
#include <SDL2/SDL.h>

#include "Model.h"
#include "View_SDL.h"

Visual * sdl_initialize(){
    Visual * g=(Visual *)malloc(sizeof(Visual));
    if(SDL_Init(SDL_INIT_EVERYTHING)){
        perror("Error SDL initializing");
        exit(EXIT_FAILURE);
    }
    g->window=SDL_CreateWindow("WINDOW_TITLE",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,0);
    if(!g->window){
        perror("Error initializing window");
        exit(EXIT_FAILURE);
    }
    g->renderer = SDL_CreateRenderer(g->window,-1,0);
    if(!g->renderer){
        perror("Pb init renderer");
        exit(EXIT_FAILURE);
    }
    SDL_RenderClear(g->renderer);

    SDL_RenderPresent(g->renderer); 
    return g;
}

void cleanup(Visual * v){
    SDL_DestroyRenderer(v->renderer);
    SDL_DestroyWindow(v->window);
    SDL_Quit();
    free(v);
}