#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <stdio.h>
#include <gamespace.h>
#include <vector>
#include <memory>
#include <strawberry.h>
#include <Snake.h>

// void close(SDL_Window* window, SDL_Renderer* renderer);

SDL_Window * init_window(int screen_width, int screen_height)
{
    SDL_Window* window = NULL;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		window = SDL_CreateWindow( "Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		}

		return window;
	}
}

SDL_Renderer * init_renderer(int screen_width, int screen_height, SDL_Window* window)
{
    SDL_Renderer* renderer = NULL;

    //Create vsynced renderer for window
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( renderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Initialize renderer color
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

        //Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        }
    }
    return renderer;

}

void close(SDL_Window* window, SDL_Renderer* renderer)
{
    //Destroy window
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //screen dimensions
    const int SCREEN_WIDTH = 840;
    const int SCREEN_HEIGHT = 840;
    //for now, the valid region for the caterpillar to go will be hard-coded
    const int GAMEPLAY_WIDTH = 800;
    const int GAMEPLAY_HEIGHT = 800;

    SDL_Window * window = init_window(SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Renderer * renderer = init_renderer(SCREEN_WIDTH, SCREEN_HEIGHT, window);

    if (window == NULL)
    {
        printf("Window failed to initialize...");
    }
    else
    {
        if (renderer == NULL)
        {
            printf("Renderer failed to initialize...");
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Instantiate the gamespace
            Gamespace background(GAMEPLAY_WIDTH, GAMEPLAY_HEIGHT);\

            //Instantiate the Snake
            Snake snake(GAMEPLAY_HEIGHT, GAMEPLAY_WIDTH);

            //The target
            Strawberry strawberry(GAMEPLAY_WIDTH, GAMEPLAY_HEIGHT);

            //Include a dynamic array to track the tail
            std::vector<Segment> tail;

            /*
            We don't want to render the head every single pass through the while loop,
            so we'll set up a counter to count from 0 to 4, thereby rendering only
            every 5th pass.  Increasing max_count decreases the speed of the head.
            */
            int counter = 0;
            int max_count = 3;

            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    snake.handle_event(e);
                }
                //Clear the renderer
                //SDL_RenderClear(renderer);

                //Render the Gamespace (background)
                background.render(renderer);

                //render the target strawberry
                strawberry.render(renderer);

                //render the snake
                snake.render(renderer);

                if (counter == max_count)
                {
                    counter = 0;
                    snake.move_snake();
                    if (snake.self_collision())
                    {
                        snake.destroy_tail();
                    }
                    if (strawberry.collision(snake))
                    {
                        snake.add_segment();
                        strawberry.place_random();
                    }
                }
                counter++;
                SDL_RenderPresent(renderer);

            }
        }
    }
    close( window, renderer );

    return 0;
}
