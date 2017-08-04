#ifndef SNAKE_H
#define SNAKE_H
#include <SDL.h>
#include <segment.h>
#include <vector>
#include <gameinput.h>


class Snake
{
    public:
        Snake(int gameplay_height, int gameplay_width, int segment_hieght = 20, int segment_width = 20);
        bool self_collision();
        SDL_Rect head_position();
        void add_segment();
        void handle_event(SDL_Event e);
        void move_snake();
        void render(SDL_Renderer* renderer);
        void destroy_tail();

    private:
        int H_HEIGHT; //Dimensions of the snake's segments
        int H_WIDTH;
        int x_bound;  //Dimensions of the gameplay area
        int y_bound;
        Gameinput move_direction;
        Segment head;
        std::vector<Segment> tail;

};

#endif // SNAKE_H
