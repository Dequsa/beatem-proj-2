#include "map_handler.h"
#include "utility.h"
#include <cstdio>

Map::Map(SDL_Renderer* renderer, const char* file_path)
{

    texture_ = InGameManagers::LoadTexture(renderer, file_path, width_, height_);
}

Map::~Map()
{
    if (texture_ != nullptr)
    {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }
}