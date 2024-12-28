#include "../header/View_Ncurses.h"
#include <stdlib.h>

void init_view_ncurses() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
}

void cleanup_view_ncurses() {
    endwin();
}

void render_game_ncurses(Board *board, Score *score) {
    clear();

    for (int i = 0; i < board->width; i++) {
        mvprintw(0, i, "#");
        mvprintw(board->height - 1, i, "#");
    }
    for (int i = 0; i < board->height; i++) {
        mvprintw(i, 0, "#");
        mvprintw(i, board->width - 1, "#");
    }

    attron(COLOR_PAIR(1));
    Tail *current = board->p1->tail;
    while (current) {
        mvprintw(current->y, current->x, "1");
        current = current->tail;
    }
    mvprintw(board->p1->y, board->p1->x, "1");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    current = board->p2->tail;
    while (current) {
        mvprintw(current->y, current->x, "2");
        current = current->tail;
    }
    mvprintw(board->p2->y, board->p2->x, "2");
    attroff(COLOR_PAIR(2));

    mvprintw(board->height, 0, "Player 1: %d", score->scoreP1);
    mvprintw(board->height + 1, 0, "Player 2: %d", score->scoreP2);

    refresh();
}
