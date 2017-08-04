#include "segment.h"
#include <memory>

Segment::Segment(int x, int y)
{
    //set the width and height of the head here: it won't need to be changed after initialization
    current_position.h = 20;
    current_position.w = 20;

    current_position.x = x;
    current_position.y = y;

}

void Segment::move_segment(int x, int y)
{
    current_position.x = x;
    current_position.y = y;
}

SDL_Rect Segment::get_position()
{
    return current_position;
}

void Segment::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor( renderer, color[0], color[1], color[2], color[3] );
    SDL_RenderFillRect(renderer, &current_position);

}

void Segment::x_move(int x)
{
    current_position.x = x;
}

void Segment::y_move(int y)
{
    current_position.y = y;
}
