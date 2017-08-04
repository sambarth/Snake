#ifndef STRAWBERRY_H
#define STRAWBERRY_H
#include <SDL.h>
#include <Snake.h>


class Strawberry
{
    public:
        Strawberry(int gameplay_width, int gameplay_height);
        void place_random();
        SDL_Rect get_position();
        bool collision(Snake snake);
        void render(SDL_Renderer* renderer);

    private:
        int max_x;
        int max_y;
        SDL_Rect current_position;

};

#endif // STRAWBERRY_H
