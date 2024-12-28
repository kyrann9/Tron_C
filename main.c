#include <stdio.h>

#include "./header/Controler.h"
#include <unistd.h>

#define FRAME_DELAY 100000

int main(int argc,char * argv[]) {
    if(argc<2){
        printf("USE CASE : \n%s [1-2]\1 : SLD; 2 : NCurses\n",argv[0]);
        return 0;
    }
    else{ 
        if(atoi(argv[1])>3 && atoi(argv[1])<0){
            printf("NON VALID NUMBER IN OPTION\n VALUE MUST BE BETWEEN 1 AND 2\n");
            return 0;
        }
    }
    int mdj=atoi(argv[1]);
    Board *board = init_game();
    Score *score = init_Score();
    if(mdj==0){
        init_view_ncurses();

        init_controller();
        Visual * view_SDL=sdl_initialize();
        
        mainLoop(board,score,view_SDL,mdj);

        cleanup(view_SDL); 

        cleanup_view_ncurses();
        cleanup_controller();
    }
    if(mdj==1){
        Visual * view_SDL=sdl_initialize();
        
        mainLoop(board,score,view_SDL,mdj);

        cleanup(view_SDL); 
    }

    if(mdj==2){
    init_view_ncurses();

    init_controller();

    mainLoop(board,score,NULL,mdj);

    cleanup_view_ncurses();
    cleanup_controller();
    }

    destroy_game(board,score);
    return 0;
}
