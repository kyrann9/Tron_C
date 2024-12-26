#include <stdio.h>
#include <SDL2/SDL.h>

#include "Model.h"
#include "View_SDL.h"

#define CELL_SIZE 15

Visual * sdl_initialize(){
    Visual * view=(Visual *)malloc(sizeof(Visual));
    if(SDL_Init(SDL_INIT_EVERYTHING)){
        perror("Error SDL initializing");
        exit(EXIT_FAILURE);
    }
    view->window_width = (WIDTH * CELL_SIZE) + 1;
    view->window_height = (HEIGHT * CELL_SIZE) + 1+150;
    view->window=SDL_CreateWindow("Tron",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,view->window_width,view->window_height,0);
    if(!view->window){
        perror("Error initializing window");
        exit(EXIT_FAILURE);
    }
    view->renderer = SDL_CreateRenderer(view->window,-1,0);
    if(!view->renderer){
        perror("Pb init renderer");
        exit(EXIT_FAILURE);
    }

    SDL_RenderPresent(view->renderer); 
    return view;
}

void cleanup(Visual * v){
    SDL_DestroyRenderer(v->renderer);
    SDL_DestroyWindow(v->window);
    SDL_Quit();
    free(v);
}

void draw_grid(Board* b,Visual * view){
    SDL_SetRenderDrawColor(view->renderer,22,22,22,255);
    SDL_RenderClear(view->renderer);
    SDL_RenderPresent(view->renderer);
    SDL_SetRenderDrawColor(view->renderer,77,77,77,255);
    for(int x=0;x<view->window_width*CELL_SIZE+1;x+=CELL_SIZE){
        SDL_RenderDrawLine(view->renderer,x,150+1,x,view->window_height);
    }
    for(int y=150;y<view->window_height*CELL_SIZE+1;y+=CELL_SIZE){
        SDL_RenderDrawLine(view->renderer,0,y,view->window_width,y);
    }
    draw_player(b,view);
}

void draw_player(Board * board,Visual * view){
    SDL_SetRenderDrawColor(view->renderer,180,30,180,255);
    for(int x=0;x<CELL_SIZE;x++)SDL_RenderDrawLine(view->renderer,board->p1->x*CELL_SIZE+x,board->p1->y*CELL_SIZE+150,board->p1->x*CELL_SIZE+x,board->p1->y*CELL_SIZE+CELL_SIZE+150);
    SDL_SetRenderDrawColor(view->renderer,30,30,180,255);
    for(int x=0;x<CELL_SIZE;x++)SDL_RenderDrawLine(view->renderer,board->p2->x*CELL_SIZE+x,board->p2->y*CELL_SIZE+150,board->p2->x*CELL_SIZE+x,board->p2->y*CELL_SIZE+CELL_SIZE+150);
    SDL_RenderPresent(view->renderer);
}
