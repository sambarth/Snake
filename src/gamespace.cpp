#include "gamespace.h"
#include <SDL.h>

Gamespace::Gamespace(int width, int height) : width(width), height(height)
{
    viewport.h = width;
    viewport.w = height;
    viewport.x = 20;
    viewport.y = 20;
    color[0] = 0xFF;
    color[1] = 0x71;
    color[2] = 0xce;
    color[3] = 0xFF;

}

void Gamespace::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor( renderer, color[0], color[1], color[2], color[3] );
    SDL_RenderFillRect( renderer, &viewport );
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

Gamespace::~Gamespace()
{
}
