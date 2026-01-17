#include "structs.h"

namespace InfoBarConstants
{
    constexpr const char *CHARSET_PATH = "assets/bitmap/cs8x8.bmp";
    constexpr const char *TITLE = "Player health:";
    constexpr const char *CONTROLS = "\x18 - up | \x19 - down | \x1A - left | \x1B - right | \x5A - LIGHT ATTACK | \x58 - HEAVY ATTACK";
}

class InfoBar
{
private:
    float time_;
    char *text_;
    float scale_;
    dimensions_t size_;
    position_t pos_;
    SDL_Surface *charset_;
    SDL_Surface *surface_;
    SDL_Texture *texture_;


    // time update for time displaying
    void update_timer(float dt);

public:
    InfoBar(position_t pos, dimensions_t size, SDL_Renderer *renderer);
    ~InfoBar();

    // draw info bar on the screen
    void display_infobar(SDL_Renderer *renderer);

    void update_infobar(const int player_health, const int enemy_health, float delta_time, SDL_Renderer *renderer);
};
