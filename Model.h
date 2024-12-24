#ifndef MODEL_H
#define MODEL_H

struct _tail {
    struct _tail * tail;
    int x,y;
};
typedef struct _tail Tail;

struct _player{
    Tail * tail;
    int x,y;
    short dirx,diry;
};
typedef struct _player Player;

typedef struct {
    Player * p1;
    Player * p2;
    int width,height;
}Board;

typedef struct{
    short scoreP1,scoreP2;
}Score;


Board * init_game();
void destroy_player(Tail * p);
void destroy_game(Board * b,Score *s);
int collision_check(Board * board, Player * player);
void add_tail(Player ** p);
void direction_up(Board* b, int nbPLayer);
void direction_right(Board* b, int nbPLayer);
void direction_down(Board* b, int nbPLayer);
void direction_left(Board* b, int nbPLayer);

#endif