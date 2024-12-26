#ifndef VIEW_SDL_H
#define VIEW_SDL_H
    typedef struct{
        SDL_Window * window;
        SDL_Renderer * renderer;
        int window_width;
        int window_height;
    }Visual;

    Visual * sdl_initialize();
    void cleanup(Visual * v);
    void draw_grid(Board * b,Visual * view);
    void draw_player(Board * board,Visual * view);
#endif