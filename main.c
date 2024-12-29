#include <stdio.h>

#include "./header/Controler.h"
#include <unistd.h>

#define FRAME_DELAY 100000

int main(int argc,char * argv[]) {
    if(argc>1){
        printf("USE CASE : \n%s\n",argv[0]);
        return 0;
    }
    int mdj,nb_j;
    do{
        printf("Interface used : (1 = SDL, 2 = Ncurses, 0 = Both )\n");
        scanf("%d",&mdj);
    }while((mdj>2 || mdj<0));
    do{
        printf("Number of player : (1 = Singleplayer, 2 = Multiplayer\n");
        scanf("%d",&nb_j);
    }while((nb_j>2 || nb_j<0));

    if(argc>1)nb_j=atoi(argv[2])%2;
    Board *board = init_game();
    Score *score = init_Score();
    if(mdj==0){
        init_view_ncurses();

        init_controller();
        Visual * view_SDL=sdl_initialize();
        
        mainLoop(board,score,view_SDL,mdj,nb_j);

        cleanup(view_SDL); 

        cleanup_view_ncurses();
        cleanup_controller();
    }
    if(mdj==1){
        Visual * view_SDL=sdl_initialize();
        
        mainLoop(board,score,view_SDL,mdj,nb_j);

        cleanup(view_SDL); 
    }

    if(mdj==2){
    init_view_ncurses();

    init_controller();

    mainLoop(board,score,NULL,mdj,nb_j);

    cleanup_view_ncurses();
    cleanup_controller();
    }

    destroy_game(board,score);
    return 0;
}
