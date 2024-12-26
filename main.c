#include "Model.h"
#include "Controler.h"
#include "View_Ncurses.h"
#include <unistd.h>

#define FRAME_DELAY 100000

int main() {
    Board *board = init_game();
    Score *score = init_Score();

    init_view_ncurses();

    init_controller();

    while (!gameOver(score)) {
        render_game_ncurses(board, score);

        process_input(board);

        add_tail(&board->p1);
        add_tail(&board->p2);

        update_score(board, score);

        usleep(FRAME_DELAY);
    }

    cleanup_view_ncurses();
    cleanup_controller();
    destroy_game(board, score);

    return 0;
}
