#include "Controler.h"
#include <stdlib.h>
#include <unistd.h>
#define FRAME_DELAY 100000

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


void process_input(Board *board) {
    int ch = getch();

    switch (ch) {
        case KEY_DOWN:
            set_direction(board, 0, DOWN);
            break;
        case KEY_UP:
            set_direction(board, 0, UP);
            break;
        case KEY_LEFT:
            set_direction(board, 0, LEFT);
            break;
        case KEY_RIGHT:
            set_direction(board, 0, RIGHT);
            break;
        case 'z':
            set_direction(board, 1, UP);
            break;
            
        case 's':
            set_direction(board, 1, DOWN);
            break;
            
        case 'q':
            set_direction(board, 1, LEFT);
            break;
        case 'd':
            set_direction(board, 1, RIGHT);
            break;
    }
}

void run_game_ncurses(Board *board, Score *score) {
    init_controller();
    while (!gameOver(score)) {
        process_input(board);
        add_tail(&board->p1);
        add_tail(&board->p2);
        update_score(board, score);
        //draw_game(board, score);
        usleep(FRAME_DELAY);
    }
    

    cleanup_controller();
}
