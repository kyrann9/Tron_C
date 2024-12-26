#ifndef CONTROLER_H
#define CONTROLER_H



void initGameSDL();
int keyPressEvent(SDL_Event event,Board * board);
void mainLoop(Board * board, Score * score, Visual * view_SDL);
int dessine_joueur(Board * b,Score * s, Visual * view_SDL);
void dessine(Board*b,Visual * view_SDL);
int endgame(Board *board, Score * score,Visual* view);
#endif