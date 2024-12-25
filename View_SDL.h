#ifndef VIEW_SDL_H
#define VIEW_SDL_H
    typedef struct{
        SDL_Window * window;
        SDL_Renderer * renderer;
    }Visual;

    Visual * sdl_initialize();
    void cleanup(Visual * v);
#endif