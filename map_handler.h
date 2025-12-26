#include "utility.h"

class Map
{
    private:
        SDL_Texture* map_texture_;
        int map_width_;
        int map_height_;

    public:
        // map class constructor
        Map();

        // map class destructor
        ~Map();

        // load map texture from file
        void load_map_texture(SDL_Renderer* renderer, const char* file_path);

        // getters
        SDL_Texture* get_map_texture() { return map_texture_; }
        int get_map_width() { return map_width_; }
        int get_map_height() { return map_height_; }

};