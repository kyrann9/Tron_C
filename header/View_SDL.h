#ifndef VIEW_SDL_H
#define VIEW_SDL_H

#include "Model.h"

    typedef struct{
        SDL_Window * window;
        SDL_Renderer * renderer;
        int window_width;
        int window_height;
    }Visual;

    Visual * sdl_initialize();
    void cleanup(Visual * v);
    void draw_grid(Board * b,Visual * view,Score *score);
    void draw_player(Board * board,Visual * view);
    void draw_score(Score * s,Visual * view);
    void draw_number(int score,Visual *view, int depx,int depy);
    void anim_fin_SDL(Visual *view,Score * s);
#endif