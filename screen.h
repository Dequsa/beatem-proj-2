#pragma once
#include <SDL.h>
#include "structs.h"

typedef struct
{
    SDL_Window *game_window;
    SDL_Renderer *game_renderer;
    position_t camera_position;
} screen_t;

bool screen_init_SDL();

void close(screen_t *screen);

void screen_create(screen_t *screen);

class MainMenu
{
private:
    const char *FILE_PATH = "assets/maps/main_menu.bmp";
    const char *WIN_PATH = "assets/maps/gg.bmp";
    const int ms_lock = 16;

    bool is_in_menu_;
    SDL_Texture *background_;
    SDL_Texture *win_bg_;
    SDL_Texture *sprite_;

    void handle_events(bool &in_action ,bool &quit);

    void update_display(SDL_Renderer *screen, bool has_won);

public:
    MainMenu(SDL_Renderer *screen, bool &in_action);
    ~MainMenu();

    void show(SDL_Renderer *screen, bool &in_action, bool &quit, bool has_won);
};