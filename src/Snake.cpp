#include "Snake.h"
#include <SDL.h>
#include <vector>
#include <SDL.h>
#include <segment.h>

Snake::Snake(int gameplay_height, int gameplay_width, int segment_height, int segment_width) : head(0, 0)
{
    head.move_segment(gameplay_width / 2 , gameplay_height / 2);
    move_direction = down;

    H_HEIGHT = segment_height;
    H_WIDTH = segment_width;

    x_bound = gameplay_width;
    y_bound = gameplay_height;

}

void Snake::render(SDL_Renderer* renderer)
{
    head.render(renderer);
    for(std::vector<Segment>::iterator it = tail.begin(); it != tail.end(); ++it)
    {
        (* it).render(renderer);
    }

}

bool Snake::self_collision()
{
    for(std::vector<Segment>::iterator it = tail.begin(); it != tail.end(); ++it)
    {
        if (((* it).get_position().x == head.get_position().x) && ((* it).get_position().y == head.get_position().y))
        {
            return true;
        }
    }
    return false;
}

SDL_Rect Snake::head_position()
{
    return head.get_position();
}

void Snake::add_segment()
{
    //We're going to sit the newest segment right on top of the last segment in the tail (or the head if the tail is length 0)
    if (tail.empty()) //In this case, we'll plop the new segment down right on top of the the head.
    {
        Segment added_segment(head.get_position().x, head.get_position().y);
        tail.push_back(added_segment);
    }
    else
    {
        Segment added_segment(tail.back().get_position().x, tail.back().get_position().y);
        tail.push_back(added_segment);
    }

}

void Snake::handle_event(SDL_Event e)
{
    switch (e.key.keysym.sym)
    {
        case SDLK_DOWN:
            move_direction = down;
            break;
        case SDLK_UP:
            move_direction = up;
            break;
        case SDLK_RIGHT:
            move_direction = right;
            break;
        case SDLK_LEFT:
            move_direction = left;
            break;
        default:
            break;

    }

}

void Snake::move_snake()
{
    //We have to work our way from the back of the snake to the front to avoid gratuitous use of temporary variables

    if (tail.size() == 1) //only one other segment, which will be moved to the current head position.
    {
        tail.front().move_segment(head.get_position().x , head.get_position().y);
    }
    else if (tail.size() > 1) //Otherwise we need to move all the remaining segments in the tail
    {
        for(int i = tail.size() - 1 ; i > 0 ; --i) //Start at the back
        {
            tail[i].move_segment(tail[i - 1].get_position().x, tail[i - 1].get_position().y);
        }
        tail.front().move_segment(head.get_position().x , head.get_position().y); //Now set the first tail segment
    }

    //For now we'll pretend to know implicitly that there is a buffer region of length 20 around the game space
    int buffer_region = 20;

    switch(move_direction) //Finally move the head
    {
        case up:
            if((head.get_position().y - H_HEIGHT) < buffer_region)
                head.y_move(y_bound); //Wrap around
            else
                head.y_move(head.get_position().y - H_HEIGHT);
            break;
        case down:
            if((head.get_position().y) > y_bound - buffer_region)
                head.y_move(buffer_region);
            else
                head.y_move(head.get_position().y + H_HEIGHT);
            break;
        case left:
            if((head.get_position().x - H_WIDTH) < buffer_region)
                head.x_move(x_bound);
            else
                head.x_move(head.get_position().x - H_WIDTH);
            break;
        case right:
            if((head.get_position().x) > x_bound - buffer_region)
                head.x_move(buffer_region);
            else
                head.x_move(head.get_position().x + H_WIDTH);
            break;
    }

}

void Snake::destroy_tail()
{
    tail.clear();
}
