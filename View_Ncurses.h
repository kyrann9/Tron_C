#ifndef VIEW_NCURSES_H
#define VIEW_NCURSES_H

#include <ncurses.h>
#include "Model.h"

void init_view_ncurses();

void cleanup_view_ncurses();

void render_game_ncurses(Board *board, Score *score);

#endif
