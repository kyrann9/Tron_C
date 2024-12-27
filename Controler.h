#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model.h"
#include <ncurses.h>

void init_controller();

void cleanup_controller();
void process_input(Board *board);
void draw_game(Board *board, Score *score);
void run_game_ncurses(Board *board, Score *score);
#endif