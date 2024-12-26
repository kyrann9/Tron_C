#include <stdio.h>
#include <SDL2/SDL.h>

#include "Model.h"
#include "View_SDL.h"
#include "View_Ncurses.h"
#include "Controler.h"

#include <stdbool.h>

/* Function Prototypes */
    /* main */
void initGameSDL(){
    Board * board=init_game();
    Score * score=init_Score();
    Visual * view_SDL=sdl_initialize();
    mainLoop(board,score,view_SDL);
}
void mainLoop(Board * board, Score * score, Visual * view_SDL){
    int quit=1;
    SDL_Event event;
    Uint32 last=SDL_GetTicks();
    dessine(board,view_SDL);
    while(quit){
        if(gameOver(score)){
            //Code to check if user wants to restart ? Or to avoid them moving objects when the game stopped 
            quit=endgame(board,score,view_SDL);
        }
        else{
            while (SDL_PollEvent(&event))
                {
                switch (event.type)
                {
                case SDL_QUIT:
                    quit=0;
                    break;
                case SDL_KEYDOWN:
                    quit=keyPressEvent(event,board);
                    break;
                default:
                    break;
                }
            }
            if(SDL_GetTicks()-last>=75){
                quit=dessine_joueur(board,score,view_SDL);
                last=SDL_GetTicks();
            }
        }
        SDL_Delay(floor(16.666f)); //Caps the FPS
    }
    
    destroy_game(board,score);
    cleanup(view_SDL);
}


void dessine(Board * b,Visual * view_SDL){
    draw_grid(b,view_SDL);
}


int dessine_joueur(Board * board, Score* score, Visual * view_SDL){
    SDL_Event event;
    add_tail(&(board->p1));
    add_tail(&(board->p2));
    if(update_score(board,score) && !gameOver(score)){
        int continu=1;
        while(continu==1){
        while (SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT)continu=0;
            else continu=keyPressEvent(event,board);
        }
    }
    dessine(board,view_SDL);
    return continu;
    }
    else draw_player(board,view_SDL);
    return 1;
}
int keyPressEvent(SDL_Event event,Board * board){
    switch(event.key.keysym.sym){
        case SDLK_ESCAPE:
            return 0; 
            break;
        case SDLK_SPACE:
            return 2;
            break;
        case SDLK_UP:
            set_direction(board,1,UP);
            break;
        case SDLK_RIGHT:
            set_direction(board,1,RIGHT);
            break;
        case SDLK_DOWN:
            set_direction(board,1,DOWN);
            break;
        case SDLK_LEFT:
            set_direction(board,1,LEFT);
            break;

        case SDLK_z:
            set_direction(board,0,UP);
            break;
        case SDLK_d:
            set_direction(board,0,RIGHT);
            break;
        case SDLK_s:
            set_direction(board,0,DOWN);
            break;
        case SDLK_q:
            set_direction(board,0,LEFT);
            break;
        default:
            break;
    }
    return 1;
}
int endgame(Board* board,Score * score,Visual *view){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if(event.type==SDL_QUIT){
            return 0;
        }
        else{
            switch(event.key.keysym.sym){
                case SDLK_ESCAPE:
                    return 0;
                    break;
                case SDLK_SPACE:
                    reset_game(board,score);
                    dessine(board,view);
                default:
                    break;
            }
        }
    }
    return 1;
}

int main( int argc, char *argv[] ){
    initGameSDL();   
}