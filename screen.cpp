#include "screen.h"
#include "utility.h"
#include <SDL.h>
#include <cstdio>
#define SDL_MAIN_HANDLED
#define SPRITE_LOCATION_STRING_LENGTH 36

bool screen_check_SDL() 
{
    bool success = true; 
    // initialization of SDL VDIE AND TIMER for displaying time and everything else
	if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) < 0) 
    {
		printf("error during initialization of SDL err: %s \n", SDL_GetError());
		success = false;
	}
	return success;
}

// initialize SDL functions
bool screen_init_SDL()
{
    SDL_SetMainReady();

    if(!screen_check_SDL())
        return false;

    return true;
}

bool screen_create_window(screen_t* screen) 
{
    
    // init flag
    bool success = true;

    // create window
    screen->game_window = SDL_CreateWindow("Beat-Em game window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // check for errors
    if(screen->game_window == nullptr) 
    {
        printf("err while creating window: %s\n", SDL_GetError());
        success = false;
    } 
    else 
    {
        // getting windows surface
        screen->game_surface = SDL_GetWindowSurface(screen->game_window);
    }
    return success;
}

bool load_all_sprites_to_memory(screen_t* screen)
{
    // loader flag
    bool success = true;

    for (int n = 0; n < NUMBER_OF_ENTITIES; ++n)
    {
        // "assets/sprites/sprite_entity_X.bmp"
        char destination[SPRITE_LOCATION_STRING_LENGTH];
        snprintf(destination, sizeof(destination), "assets/sprites/sprite_entity_%d.bmp", n);
        
        screen->sprites[n] = SDL_LoadBMP(destination);

        if(screen->sprites[n] == nullptr) 
        {
            printf("err while loading test sprite number: %d    : %s \n",n , SDL_GetError());
            success = false;
        }
    }

    return success;
} 


void close(screen_t* screen) 
{

    // dealocate surface
    SDL_FreeSurface(screen->sprites[0]);
    screen->sprites = nullptr;

    // destroy the window
    SDL_DestroyWindow(screen->game_window);
    screen->game_window = nullptr;

    SDL_Quit();
}

void screen_create(screen_t* screen)
{
    if(!screen_init_SDL())
	{
		printf("skill issue");
		system("pause");
	} 
	else 
	{
		if(!screen_create_window(screen))
		{
			printf("failed to create window");
			system("pause");
		}
		else
		{
			if(!load_all_sprites_to_memory(screen))
			{
				printf("failed to load test sprite");
				system("pause");
			}
			else
			{
                // main game loop
				SDL_Event e; 
				bool quit = false; 
				while( quit == false )
				{ 
					while( SDL_PollEvent( &e ) )
					{ 
						if( e.type == SDL_QUIT ) quit = true;
					}

                    for(int n = 0; n < NUMBER_OF_ENTITIES; ++n)
                    {
                        draw_sprite(screen->game_surface, screen->sprites[n], SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f, 1.05f);
                    } 
                    SDL_UpdateWindowSurface(screen->game_window);
				}
			}	
		}
	}
}