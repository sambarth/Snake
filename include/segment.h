#ifndef SEGMENT_H
#define SEGMENT_H
#include <SDL.h>
#include <memory>


class Segment
{
    public:
        Segment(int x, int y);
        void move_segment(int x, int y);
        SDL_Rect get_position();
        void render(SDL_Renderer* renderer);
        void x_move(int x);
        void y_move(int y);

    private:
        SDL_Rect current_position;
        static const int H_WIDTH = 20;
        static const int H_HEIGHT = 20;
        uint8_t color[4] = {0xFF, 0xFB, 0x96, 0xFF};

};

#endif // SEGMENT_H
