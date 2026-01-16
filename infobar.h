#include "structs.h"

namespace InfoBarConstants
{
    constexpr const char *CHARSET_PATH = "assets/bitmap/cs8x8.bmp";
    constexpr const char *TITLE = "Player health: %d";
    constexpr const char *CONTROLS = "arrow up - up | arrow_down - down | arrow_left - left | arrow_right - right";
}

class InfoBar
{
private:
    float time_;
    char *text_;
    dimensions_t size_;
    position_t pos_;
    SDL_Surface *charset_;
    SDL_Surface *surface_;
    SDL_Texture *texture_;


    // time update for time displaying
    float update_timer(float dt);

public:
    InfoBar(float x, float y, int h, int w);
    ~InfoBar();

    // draw info bar on the screen
    void display_timer(SDL_Renderer *renderer);

    void update_infobar(const float player_health, const float enemy_health, float delta_time, SDL_Renderer *renderer);
};
