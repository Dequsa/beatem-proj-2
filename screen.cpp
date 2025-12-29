#include "screen.h"
#include "utility.h"
#include "player.h"
#include <cstdio>
#define SDL_MAIN_HANDLED
#define SPRITE_LOCATION_STRING_LENGTH 64

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

    if (!screen_check_SDL())
        return false;

    return true;
}

bool screen_create_window(screen_t *screen)
{

    // init flag
    bool success = true;

    // create window
    screen->game_window = SDL_CreateWindow("Beat-Em game window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, utility::SCREEN_WIDTH, utility::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // check for errors
    if (screen->game_window == nullptr)
    {
        printf("err while creating window: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // getting windows surface
        screen->game_renderer = SDL_CreateRenderer(screen->game_window, -1, SDL_RENDERER_ACCELERATED);

        if (screen->game_renderer == nullptr)
        {
            printf("err while creating renderer: %s\n", SDL_GetError());
            success = false;
        }
    }
    return success;
}


void close(screen_t *screen)
{

    // dealocate surface
    // SDL_FreeSurface(screen->sprites[0]);
    // screen->sprites = nullptr;

    // destroy the window
    SDL_DestroyWindow(screen->game_window);
    screen->game_window = nullptr;

    SDL_Quit();
}

void screen_create(screen_t *screen)
{
    if (screen_init_SDL())
    {
        if (screen_create_window(screen))
        {
            // load_all_sprites_to_memory(screen, player_sprite);
        }
    }
}
