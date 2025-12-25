#pragma once
#include <SDL.h>

namespace utility {
    constexpr int SCREEN_WIDTH = 1920;
    constexpr int SCREEN_HEIGHT = 1080;
    constexpr int NUMBER_OF_ENTITIES = 4;
    constexpr int PLAYER_NAME_MAX_LENGTH = 128;
}

void DrawString(SDL_Surface *screen, int x, int y, const char *text,SDL_Surface *charset);

void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);

void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);

void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);

void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);

void draw_sprite(SDL_Surface *screen, SDL_Surface *sprite, const float x, const float y, const float scale);