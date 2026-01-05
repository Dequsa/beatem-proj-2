#pragma once
#include <SDL.h>
#include "structs.h"

typedef struct {
    SDL_Window* game_window;
    SDL_Renderer* game_renderer;
    position_t camera_position;
}screen_t;

bool screen_init_SDL();

void close(screen_t* screen);

void screen_create(screen_t* screen);