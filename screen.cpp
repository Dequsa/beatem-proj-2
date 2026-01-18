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
            return;
        }
    }
}

// namespace MainMenu
//  {
//      void update_background()
//      {
//          DrawingFunctions::DrawSprite()
//      }

//     void check_input()
//     {
//     }

//     void show(SDL_Renderer *screen, bool &in_action, bool &quit)
//     {
//         in_action = false;

// while (is_in_menu)
// {
//     SDL_Event menu_event;
//     while (SDL_PollEvent(&menu_event) != 0)
//     {
//         if (menu_event.type == SDL_QUIT)
//         {
//             quit = true;
//             is_in_menu = false;
//             return;
//         }
//     }

//     const Uint8 *keystate = SDL_GetKeyboardState(NULL);
//     if (keystate[SDL_SCANCODE_KP_ENTER] || keystate[SDL_SCANCODE_RETURN])
//     {
//         is_in_menu = false;
//         in_action = true;
//         return;
//     }
//     else if (keystate[SDL_SCANCODE_ESCAPE])
//     {
//         quit = true;
//         is_in_menu = false;
//         return;
//     }

//     printf("is in menu\n");
//     SDL_Delay(16);
// }
//     }
// }

MainMenu::MainMenu(SDL_Renderer *screen, bool &in_action) : is_in_menu_(true)
{
    background_ = InGameManagers::LoadSpriteSheet(screen, FILE_PATH, nullptr, nullptr);
    win_bg_ = InGameManagers::LoadSpriteSheet(screen, WIN_PATH, nullptr, nullptr);
    in_action = false;
}

MainMenu::~MainMenu()
{
    FILE_PATH = nullptr;
    is_in_menu_ = false;
    background_ = nullptr;
    sprite_ = nullptr;
}

void MainMenu::handle_events(bool &in_action, bool &quit)
{
    while (is_in_menu_)
    {
        SDL_Event menu_event;
        while (SDL_PollEvent(&menu_event) != 0)
        {
            if (menu_event.type == SDL_QUIT)
            {
                quit = true;
                is_in_menu_ = false;
                return;
            }
        }

        const Uint8 *keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_KP_ENTER] || keystate[SDL_SCANCODE_RETURN])
        {
            is_in_menu_ = false;
            in_action = true;
            return;
        }
        else if (keystate[SDL_SCANCODE_ESCAPE])
        {
            quit = true;
            is_in_menu_ = false;
            return;
        }
        SDL_Delay(ms_lock);
    }
}

void MainMenu::update_display(SDL_Renderer *screen, bool has_won)
{
    if (SDL_RenderClear(screen))
    {
        printf("Err while clearing render menu: %s\n", SDL_GetError());
    }

    if (has_won)
    {
        DrawingFunctions::DrawBackground(screen, win_bg_, 0.0f, 0.0f, 1);
    }
    else
    {
        DrawingFunctions::DrawBackground(screen, background_, 0.0f, 0.0f, 1);
    }
    SDL_RenderPresent(screen);
}

void MainMenu::show(SDL_Renderer *screen, bool &in_action, bool &quit, bool has_won)
{
    update_display(screen, has_won);

    handle_events(in_action, quit);
}