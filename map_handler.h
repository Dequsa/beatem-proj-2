#pragma once
#include "utility.h"

class Map
{
    private:
        SDL_Texture* texture_;
        int width_;
        int height_;

    public:
        // map class constructor
        Map(SDL_Renderer* renderer, const char* file_path);

        // map class destructor
        ~Map();

        // getters
        SDL_Texture* get_map_texture() { return texture_; }
        int get_width() { return width_; }
        int get_height() { return height_; }

};