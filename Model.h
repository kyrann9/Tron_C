#ifndef MODEL_H
#define MODEL_H

struct _player{
    int x,y;
    struct _player * tail;
};
typedef struct _player Player;

typedef struct {
    int width,height;
    Player * p1;
    Player * p2;
}Board;

Board * init_game();
void destroy_player(Player * p);
void destroy_game(Board * b);
int collision_check(Board * board, Player * player);
void add_tail(Player ** p,int x, int y);

#endif