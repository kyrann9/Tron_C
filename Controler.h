#ifndef CONTROLER_H
#define CONTROLER_H



void initGameSDL();
int checkEvent(SDL_Event event,Board * board);
void mainLoop(Board * board, Score * score, Visual * view_SDL);
void dessine(Board * b, Visual * view_SDL);
#endif