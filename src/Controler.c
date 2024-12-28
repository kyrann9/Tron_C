#include <stdio.h>

#include "../header/Controler.h"
#include <stdbool.h>
#include <unistd.h>

#define FRAME_DELAY 100000

int nb_joueur=1;
// ----------------------------------- SDL PART ---------------------------


void mainLoop(Board * board, Score * score, Visual * view_SDL,int mode,int nb_j){
    nb_joueur=nb_j;
    if(mode<2){
        int quit=1;

        Uint32 last=SDL_GetTicks();
        draw_everything_SDL(board,view_SDL,score);
        if(!mode)render_game_ncurses(board, score);
        while(quit){
            if(gameOver(score)){
                quit=endgame(board,score,view_SDL);
            }
            else{
                quit=eventManager(board);
                if(SDL_GetTicks()-last>=75){
                    bot_decide(board,board->p2);
                    if(!mode)render_game_ncurses(board, score);
                    quit=draw_update_SDL(board,score,view_SDL);
                    last=SDL_GetTicks();
                }
            }
            if(quit && !mode){
                quit=process_input(board);
            }
            SDL_Delay(floor(16.666f)); //Caps the FPS
            usleep(1);
        }
    }
    else gameLoop(board,score);
}


int eventManager(Board* b){
    SDL_Event event; 
    while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
                return 0;
            case SDL_KEYDOWN:
                    return keyPressEvent(event,b);
            default:
                break;
        }    
    }
    return 1;
}

void draw_everything_SDL(Board * b,Visual * view_SDL,Score *score){
    draw_grid(b,view_SDL,score);
}


int draw_update_SDL(Board * board, Score* score, Visual * view_SDL){
    SDL_Event event;
    add_tail(&(board->p1));
    add_tail(&(board->p2));
    if(update_score(board,score) && !gameOver(score)){
        draw_everything_SDL(board,view_SDL,score);
        int continu=1;
        while(continu==1){
        while (SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT || event.key.keysym.sym==SDLK_ESCAPE)continu=0;
            else{
                if(event.key.keysym.sym==SDLK_SPACE){
                    continu=2;
                    reset_round(board);
                }
            }
        }
    }
    draw_everything_SDL(board,view_SDL,score);
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
        case SDLK_UP:
            if(!nb_joueur)set_direction(board,1,UP);
            break;
        case SDLK_RIGHT:
            if(!nb_joueur)set_direction(board,1,RIGHT);
            break;
        case SDLK_DOWN:
            if(!nb_joueur)set_direction(board,1,DOWN);
            break;
        case SDLK_LEFT:
            if(!nb_joueur)set_direction(board,1,LEFT);
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
    draw_everything_SDL(board,view,score);
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
                    draw_everything_SDL(board,view,score);
                default:
                    break;
            }
        }
    }
    return 1;
}

//-------------------------------------- Ncurses Part ---------------------------------------

void init_controller() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(0);
}

void cleanup_controller() {
    endwin();
}


int process_input(Board *board) {
    int ch = getch();

    switch (ch) {
        case KEY_BACKSPACE:
            return 0;
        case KEY_DOWN:
            if(!nb_joueur)set_direction(board, 1, DOWN);
            break;
        case KEY_UP:
            if(!nb_joueur)set_direction(board, 1, UP);
            break;
        case KEY_LEFT:
            if(!nb_joueur)set_direction(board, 1, LEFT);
            break;
        case KEY_RIGHT:
            if(!nb_joueur)set_direction(board, 1, RIGHT);
            break;
        case 'z':
            set_direction(board, 0, UP);
            break;
            
        case 's':
            set_direction(board, 0, DOWN);
            break;
            
        case 'q':
            set_direction(board, 0, LEFT);
            break;
        case 'd':
            set_direction(board, 0, RIGHT);
            break;
        default:
            break;
    }
    return 1;
}

void gameLoop(Board *board, Score *score){
    while (!gameOver(score)) {
        render_game_ncurses(board, score);

        process_input(board);
        if(!nb_joueur)bot_decide(board,board->p2);
        add_tail(&board->p1);
        add_tail(&board->p2);

        if(update_score(board, score)){
            reset_round(board);
        }

        usleep(FRAME_DELAY);
    }
}