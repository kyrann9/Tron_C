#include <stdio.h>
#include <SDL2/SDL.h>

#include "../header/View_SDL.h"

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

void draw_grid(Board* b,Visual * view,Score * score){
    SDL_SetRenderDrawColor(view->renderer,22,22,22,255);
    SDL_RenderClear(view->renderer);
    draw_score(score, view);
    SDL_SetRenderDrawColor(view->renderer,77,77,77,255);
    for(int i=0;i<CELL_SIZE+1;i++){
        //Draw the sides of the board
        SDL_RenderDrawLine(view->renderer,0,150+i,view->window_width,150+i);
        SDL_RenderDrawLine(view->renderer,0,view->window_height-i,view->window_width,view->window_height-i);

        SDL_RenderDrawLine(view->renderer,i,150,i,view->window_height);
        SDL_RenderDrawLine(view->renderer,view->window_width-i,150,view->window_width-i,view->window_height);

    }
    for(int x=CELL_SIZE;x<view->window_width-CELL_SIZE+1;x+=CELL_SIZE){
        SDL_RenderDrawLine(view->renderer,x,150+CELL_SIZE,x,view->window_height-CELL_SIZE);
    }
    for(int y=150+CELL_SIZE;y<view->window_height-CELL_SIZE;y+=CELL_SIZE){
        SDL_RenderDrawLine(view->renderer,CELL_SIZE,y,view->window_width-CELL_SIZE,y);
    }
    draw_player(b,view);
}

void draw_player(Board * board,Visual * view){
    SDL_SetRenderDrawColor(view->renderer,180,30,180,255);
    Tail * t=board->p1->tail;
    for(int x=0;x<CELL_SIZE;x++)SDL_RenderDrawLine(view->renderer,board->p1->x*CELL_SIZE+x,board->p1->y*CELL_SIZE+150,board->p1->x*CELL_SIZE+x,board->p1->y*CELL_SIZE+CELL_SIZE+150);
    while(t){
        for(int x=0;x<CELL_SIZE;x++)SDL_RenderDrawLine(view->renderer,t->x*CELL_SIZE+x,t->y*CELL_SIZE+150,t->x*CELL_SIZE+x,t->y*CELL_SIZE+CELL_SIZE+150);
        t=t->tail;
    }
    SDL_SetRenderDrawColor(view->renderer,30,30,180,255);
    t=board->p2->tail;
    for(int x=0;x<CELL_SIZE;x++)SDL_RenderDrawLine(view->renderer,board->p2->x*CELL_SIZE+x,board->p2->y*CELL_SIZE+150,board->p2->x*CELL_SIZE+x,board->p2->y*CELL_SIZE+CELL_SIZE+150);
    while(t){
        for(int x=0;x<CELL_SIZE;x++)SDL_RenderDrawLine(view->renderer,t->x*CELL_SIZE+x,t->y*CELL_SIZE+150,t->x*CELL_SIZE+x,t->y*CELL_SIZE+CELL_SIZE+150);
        t=t->tail;
    }

    SDL_RenderPresent(view->renderer);
}

void draw_number(int score,Visual *view, int depx,int depy){
    switch(score){
        case 0:
            for(int i=depx;i<depx+75;i++){
                SDL_RenderDrawLine(view->renderer,i,depy,i,depy+20);
                SDL_RenderDrawLine(view->renderer,i,depy+80,i,depy+100);
            }
            for(int j=depy;j<depy+100;j++){
                SDL_RenderDrawLine(view->renderer,depx,j,depx+25,j);
                SDL_RenderDrawLine(view->renderer,depx+50,j,depx+75,j);
            }
            break;
        case 1:
            for(int i=depx;i<depx+75;i++){
                if(i<depx+50)SDL_RenderDrawLine(view->renderer,i,depy,i,depy+20);
                SDL_RenderDrawLine(view->renderer,i,depy+80,i,depy+100);
            }
            for(int j=depy;j<depy+100;j++){
                SDL_RenderDrawLine(view->renderer,depx+25,j,depx+50,j);
            }
            break;
        case 2:
            for(int i=depx;i<depx+75;i++){
                SDL_RenderDrawLine(view->renderer,i,depy,i,depy+20);
                SDL_RenderDrawLine(view->renderer,i,depy+40,i,depy+60);
                SDL_RenderDrawLine(view->renderer,i,depy+80,i,depy+100);
            }
            for(int j=depy;j<depy+40;j++){
                SDL_RenderDrawLine(view->renderer,depx+50,j,depx+75,j);
                SDL_RenderDrawLine(view->renderer,depx,j+60,depx+25,j+60);
            }
            break;
        case 3:
            for(int i=depx;i<depx+75;i++){
                SDL_RenderDrawLine(view->renderer,i,depy,i,depy+20);
                SDL_RenderDrawLine(view->renderer,i,depy+40,i,depy+60);
                SDL_RenderDrawLine(view->renderer,i,depy+80,i,depy+100);
            }
            for(int j=depy;j<depy+100;j++){
                SDL_RenderDrawLine(view->renderer,depx+50,j,depx+75,j);
            }
            break;
    }
}

void draw_score(Score * s,Visual * view){
    SDL_SetRenderDrawColor(view->renderer,180,30,180,255);
    draw_number(s->scoreP1,view,100,25);
    SDL_SetRenderDrawColor(view->renderer,30,30,180,255);
    draw_number(s->scoreP2,view,view->window_width-150,25);
}

void anim_fin_SDL(Visual *view,Score * s){
    SDL_Rect r;

    (s->scoreP2>s->scoreP1)?SDL_SetRenderDrawColor(view->renderer,30,30,180,255):SDL_SetRenderDrawColor(view->renderer,180,30,180,255);
    for(int i=0;i<view->window_height;i+=4*CELL_SIZE){
    r.x = 0;
    r.y = i;
    r.w = view->window_width;
    r.h = i+4*CELL_SIZE;
        SDL_RenderFillRect(view->renderer,&r);
        SDL_RenderPresent(view->renderer);
        SDL_Delay(300);
    }
}