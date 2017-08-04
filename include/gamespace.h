#ifndef GAMESPACE_H
#define GAMESPACE_H
#include <SDL.h>


class Gamespace
{
    public:
        Gamespace(int width = 800, int height = 800);
        ~Gamespace();
        void render(SDL_Renderer* renderer);

    protected:
        int width;
        int height;
        SDL_Rect viewport;
        uint8_t color[4];

    private:
};

#endif // GAMESPACE_H
