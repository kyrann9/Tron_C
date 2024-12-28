#ifndef CONTROLER_H
#define CONTROLER_H

#include <SDL2/SDL.h>

#include "Model.h"
#include "View_SDL.h"
#include "View_Ncurses.h"

void init_controller();

void cleanup_controller();
int process_input(Board *board);
void draw_game(Board *board, Score *score);
void gameLoop(Board *board, Score *score);


int keyPressEvent(SDL_Event event,Board * board);
void mainLoop(Board * board, Score * score, Visual * view_SDL,int mode);
int draw_update_SDL(Board * b,Score * s, Visual * view_SDL);
void draw_everything_SDL(Board*b,Visual * view_SDL,Score*score);
int endgame(Board *board, Score * score,Visual* view);
int eventManager(Board* b);


#endif