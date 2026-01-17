#pragma once
#include <SDL.h>

enum class ActionSheet;

namespace utility
{
    const bool DEBUG_MODE = false;
    const int SCREEN_WIDTH = 1440;
    const int SCREEN_HEIGHT = 932;
    const int MONITOR_REFRESH_RATE = 144;
    constexpr int NUMBER_OF_ENTITIES = 4;
    constexpr const char *MAP_PATH = "assets/maps/throne room1.bmp";//"assets/maps/background.bmp";
}

namespace DrawingFunctions
{
    void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset, float scale);

    void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);

    void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color);

    void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color);

    void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);

    void DrawSprite(SDL_Renderer *screen, SDL_Texture *sprite, const float x, const float y, float scale, SDL_RendererFlip flip, int camera_x, int camera_y);

    void DrawBackground(SDL_Renderer *screen, SDL_Texture *background, float x, float y, float scale);

    void DrawFrame(SDL_Renderer *screen, SDL_Texture *sprite, const float x, const float y, float scale, SDL_RendererFlip flip, int camera_x, int camera_y, float h, float w, int current_frame, ActionSheet current_action, float offeset);
}

namespace InGameManagers
{
    SDL_Texture *LoadSpriteSheet(SDL_Renderer *screen, const char *path);
}

namespace UtilityFunctions
{
    int GetStringLength(const char *string);
}