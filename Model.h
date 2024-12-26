#ifndef MODEL_H
#define MODEL_H

#define HEIGHT 40
#define WIDTH 60
#define MAX_SCORE 3

typedef enum{
    UP,RIGHT,DOWN,LEFT
}Direction;

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
Score * init_Score();
void destroy_player(Tail * p);
void destroy_game(Board * b,Score *s);
int collision_check(Board * board, Player * player);
void add_tail(Player ** p);
int update_score(Board * game,Score * scr);
void set_direction(Board * b,int nbPlayer,Direction dir);
void reset_game(Board * board,Score * score);
void reset_round(Board * board);
int gameOver(Score *score);
#endif