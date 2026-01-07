#pragma once
#include <SDL.h>

namespace utility
{
    inline bool DEBUG_MODE = false;
    inline int SCREEN_WIDTH = 1920;
    inline int SCREEN_HEIGHT = 1080;
    inline int MONITOR_REFRESH_RATE = 144;
    constexpr int NUMBER_OF_ENTITIES = 4;
    constexpr char *MAP_PATH = "assets/maps/background.bmp";
}

namespace DrawingFunctions
{
    void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset);

    void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);

    void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);

    void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);

    void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);

    void draw_sprite(SDL_Renderer *screen, SDL_Texture *sprite, const float x, const float y, float scale, SDL_RendererFlip flip, int camera_x, int camera_y);

    void draw_background(SDL_Renderer *screen, SDL_Texture *background, float x, float y, float scale);

    void draw_frame(SDL_Renderer *screen, SDL_Texture *sprite, const float x, const float y, float scale, SDL_RendererFlip flip, int camera_x, int camera_y, float h, float w, int current_frame, float offeset);
}

namespace InGameManagers
{
    SDL_Texture *LoadSpriteSheet(SDL_Renderer *screen, const char *path);
}