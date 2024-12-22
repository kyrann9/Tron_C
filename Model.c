#include "Model.h"  

#include <stdio.h>
#include <stdlib.h>
#define HEIGHT 80
#define WIDTH 60

typedef struct{
    int score1,score2;
}Score;

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
    b->p1->y=5;
    b->p2=(Player *)malloc(sizeof(Player));
    if(!b->p2){
        perror("Error Player allocation");
        exit(EXIT_FAILURE);
    }
    b->p2->x=10;
    b->p2->y=10;

}

void destroy_player(Player * p){
    if(p){
        destroy_player(p->tail);
        free(p);
    }
}
void destroy_game(Board * b){
    destroy_player(b->p1);
    destroy_player(b->p2);
    free(b);
}

int collision_check(Board * board, Player * player){
    int nb_col=0; //there will always be a collision with their own heads, so we check for 2 collision
    Player * parc=board->p1;
    while(parc!=NULL){
        if(parc->x && parc->y){
            nb_col++;
            if(nb_col>1){printf("p1 collision\n");return 1;}
        }
        parc=parc->tail;
    }
    parc=board->p2;
    while(parc!=NULL){
        if(parc->x && parc->y){
            nb_col++;
            if(nb_col>1){printf("p2 collision\n");return 1;}
        }
        parc=parc->tail;
    }
    printf("Pas de collision\n");
    return 0;
}
void add_tail(Player ** p,int x, int y){
    Player * nhead=(Player *)malloc(sizeof(Player));
    if(!nhead){
        perror("Error Player Allocation");
        exit(EXIT_FAILURE);
    }
    nhead->x=x;nhead->y=y;
    nhead->tail=*p;
    *p=nhead;
}

int main(){
    Board * b=init_game();
    add_tail(&(b->p2),9,9);
    add_tail(&(b->p1),10,10);
    collision_check(b,b->p1);
    destroy_game(b);
}
