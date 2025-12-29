#include "map_handler.h"
#include "utility.h"
#include <cstdio>

Map::Map(SDL_Renderer* renderer, const char* file_path)
{
    // Load the map image
    SDL_Surface* temp_surface = SDL_LoadBMP(file_path);
    if (temp_surface == nullptr)
    {
        printf("Error loading map: %s\n", SDL_GetError());
        return;
    }

    // Create texture from surface
    texture_ = SDL_CreateTextureFromSurface(renderer, temp_surface);
    if (texture_ == nullptr)
    {
        printf("Error creating texture from surface: %s\n", SDL_GetError());
        return;
    }

    // Get the dimensions of the loaded map
    width_ = temp_surface->w;
    height_ = temp_surface->h;

    // Free the temporary surface
    SDL_FreeSurface(temp_surface);
}

Map::~Map()
{
    if (texture_ != nullptr)
    {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }
}