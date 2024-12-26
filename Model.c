#include "Model.h"  

#include <stdio.h>
#include <stdlib.h>


Board * init_game(){
    Board * b=(Board *)malloc(sizeof(Board));
    if(!b){
        perror("Error Board allocation");
        exit(EXIT_FAILURE);
    }
    b->height=HEIGHT;
    b->width=WIDTH;
    b->p1=(Player *)malloc(sizeof(Player));
    if(!b->p1){
        perror("Error Player allocation");
        exit(EXIT_FAILURE);
    }
    b->p1->x=WIDTH/8;
    b->p1->y=HEIGHT/2;
    b->p1->dirx=1,b->p1->diry=0;
    b->p1->tail=NULL;
    b->p2=(Player *)malloc(sizeof(Player));
    if(!b->p2){
        perror("Error Player allocation");
        exit(EXIT_FAILURE);
    }
    b->p2->x=(7*WIDTH)/8+1;
    b->p2->y=HEIGHT/2;
    b->p2->dirx=-1,b->p2->diry=0;
    b->p2->tail=NULL;
    return b;
}

Score * init_Score(){
    Score * s=(Score *)malloc(sizeof(Score));
    s->scoreP1=0; s->scoreP2=0;
    return s;
}
void destroy_player(Tail * t){
    if(t){
        destroy_player(t->tail);
        free(t);
    }
}
void destroy_game(Board * b,Score *s){
    Tail * t=b->p1->tail;
    destroy_player(b->p1->tail);
    t=b->p2->tail;
    free(b->p1);
    destroy_player(b->p2->tail);
    free(b->p2);
    free(s);
    free(b);
}

int collision_check(Board * board, Player * player){
    if(player->x<0 || player->y<0 || player->x>=WIDTH || player->y>=HEIGHT) return 1;
    //Cette condition est très longue pck cette fonction ne sait pas quelle joueur elle check, à modifié peut-être ?
    if(board->p1->x==player->x && board->p1->y==player->y && board->p2->x==player->x && board->p2->y==player->y)return 1;
    Tail * parc=board->p1->tail;
    while(parc!=NULL){
        if(parc->x==player->x && parc->y==player->y){
            return 1;
        }
        parc=parc->tail;
    }
    parc=board->p2->tail;
    while(parc!=NULL){
        if(parc->x==player->x && parc->y==player->y){
            return 1;
        }
        parc=parc->tail;
    }
    return 0;
}

void set_direction(Board * b,int nbPlayer,Direction dir){

    Player * player =nbPlayer? b->p2: b->p1;
    int sauvx=player->dirx,sauvy=player->diry;
    switch(dir){
        case UP: player->dirx=0;player->diry=-1;
        break;
        case DOWN: player->dirx=0;player->diry=1;
        break;
        case LEFT: player->dirx=-1;player->diry=0;
        break;
        case RIGHT: player->dirx=1;player->diry=0;
        break;
    }
    if(player->tail && player->tail->x==player->dirx+player->x && player->tail->y==player->y+player->diry){
        player->dirx=sauvx;player->diry=sauvy;
    }
}
void add_tail(Player ** p){
    Tail * nhead=(Tail *)malloc(sizeof(Tail));
    if(!nhead){
        perror("Error Tail Allocation");
        exit(EXIT_FAILURE);
    }
    nhead->x=(*p)->x;nhead->y=(*p)->y;
    nhead->tail=(*p)->tail;
    (*p)->tail=nhead;
    (*p)->x+=(*p)->dirx,(*p)->y+=(*p)->diry;
}
void reset_game(Board * board,Score * score){
    reset_round(board);
    score->scoreP1=0; score->scoreP2=0;
}
void reset_round(Board * board){
    if(!board)return;
    destroy_player(board->p1->tail);
    destroy_player(board->p2->tail);
    board->p1->tail=NULL;
    board->p2->tail=NULL;
    board->p1->x=WIDTH/8; board->p1->y=HEIGHT/2; board->p1->dirx=1; board->p1->diry=0;
    board->p2->x=(7*WIDTH)/8+1; board->p2->y=HEIGHT/2; board->p2->dirx=-1; board->p2->diry=0;
}

int update_score(Board * game,Score * scr){
    int tmp1,tmp2;
    tmp1=collision_check(game,game->p1);
    tmp2=collision_check(game,game->p2);
    if(tmp1 && !tmp2){
        scr->scoreP2++;
        reset_round(game);
        return 1;
    }
    if(tmp2 && !tmp1){
        scr->scoreP1++;
        reset_round(game);
        return 1;
    }
    if(tmp1 && tmp2){
        reset_round(game);
        return 1;
    }
    return 0;
}

int gameOver(Score *score){
    return (score->scoreP1>=MAX_SCORE || score->scoreP2>=MAX_SCORE);
}
