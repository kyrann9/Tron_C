#include "Model.h"  

#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 80
#define WIDTH 60
#define MAX_SCORE 3

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
    b->p1->x=5;
    b->p1->y=10;
    b->p1->dirx=1,b->p1->diry=0;
    b->p1->tail=NULL;
    b->p2=(Player *)malloc(sizeof(Player));
    if(!b->p2){
        perror("Error Player allocation");
        exit(EXIT_FAILURE);
    }
    b->p2->x=10;
    b->p2->y=10;
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
    //Cette condition est très longue pck cette fonction ne sait pas quelle joueur elle check, à modifié peut-être ?
    if(player->x<=0 || player->y<=0 || player->x>=WIDTH || player->y>=HEIGHT)return 1;
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

void direction_left(Board* b, int nbPLayer){
    if(nbPLayer){
        b->p2->dirx=-1; b->p2->diry=0;
        return;
    }
    b->p1->dirx=-1; b->p1->diry=0;
}
void direction_right(Board* b, int nbPLayer){
    if(nbPLayer){
        b->p2->dirx=1; b->p2->diry=0;
        return;
    }
    b->p1->dirx=1; b->p1->diry=0;
}
void direction_down(Board* b, int nbPLayer){
    if(nbPLayer){
        b->p2->dirx=0; b->p2->diry=1;
        return;
    }
    b->p1->dirx=0; b->p1->diry=1;
}
void direction_up(Board* b, int nbPLayer){
    if(nbPLayer){
        b->p2->dirx=0; b->p2->diry=-1;
        return;
    }
    b->p1->dirx=0; b->p1->diry=-1;
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

void update_score(Board * game,Score * scr){
    int tmp1,tmp2;
    tmp1=collision_check(game,game->p1);
    tmp2=collision_check(game,game->p2);
    if(tmp1 && !tmp2)scr->scoreP2++;
    if(tmp2 && !tmp1)scr->scoreP1++;
}
int main(){
    Board * b=init_game();
    Score * s=init_Score();
    
    for(int i=0;i<5;i++){
        if(i==4)direction_up(b,0);
        add_tail(&(b->p2));
        add_tail(&(b->p1));

        update_score(b,s);
        printf("score P1=%d, socr P2=%d\n",s->scoreP1,s->scoreP2);
    }
    destroy_game(b,s);
}
