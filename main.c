#include <stdio.h>

#include "Controler.h"
#include <unistd.h>

#define FRAME_DELAY 100000

int main(int argc,char * argv[]) {
    if(argc<2){
        printf("USE CASE :\n%s [0-2]\n0 : Both SDL and Ncurses; 1 : Only SLD; 2 : Only NCurses\n",argv[0]);
        return 0;
    }
    else{ 
        if(atoi(argv[1])>3){
            printf("NON VALID NUMBER IN OPTION\n VALUE MUST BE BETWEEN 0 AND 2\n");
            return 0;
        }
    }
    int mdj=atoi(argv[1]);
    Board *board = init_game();
    Score *score = init_Score();
    

    if(mdj==0){
        loop_both(board,NULL,score);
    }
    if(mdj==1){
        Visual * view_SDL=sdl_initialize();
        
        SDLLoop(board,score,view_SDL);

        cleanup(view_SDL); 
    }

    if(mdj==2){
    init_view_ncurses();

    init_controller();

    gameLoop(board,score);

    cleanup_view_ncurses();
    cleanup_controller();
    }

    destroy_game(board,score);
    return 0;
}
