#include "strawberry.h"
#include <random>
#include <SDL.h>

Strawberry::Strawberry(int gameplay_width, int gameplay_height)
{
    //Hard-coded size for the strawberry for now
    current_position.h = 20;
    current_position.w = 20;

    //We'll assume that the gameplay width and height are evenly divisible by 20 for now
    //We abstract the gameplay area into a grid of 20x20 squares
    max_x = gameplay_width / 20;
    max_y = gameplay_height / 20;

    this->place_random();
}

void Strawberry::place_random()
{
    current_position.x = (rand() % (max_x - 1) + 1) * 20;
    current_position.y = (rand() % (max_y - 1) + 1) * 20;
}

SDL_Rect Strawberry::get_position()
{
    return current_position;
}

bool Strawberry::collision(Snake snake)
{
    return ((snake.head_position().x == current_position.x) && (snake.head_position().y == current_position.y));
}

void Strawberry::render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect(renderer, &current_position);

}

