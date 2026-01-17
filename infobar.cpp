#include "infobar.h"
#include "utility.h"
#include "string.h"
#include <cstdio>

InfoBar::InfoBar(position_t position, dimensions_t size, SDL_Renderer *renderer) : pos_(position), size_(size), scale_(2.0f), time_(0.0f)
{
    int max_lenght_string = strlen(InfoBarConstants::CONTROLS);
    text_ = new char[max_lenght_string + 1];

    charset_ = SDL_LoadBMP(InfoBarConstants::CHARSET_PATH);
    surface_ = SDL_CreateRGBSurface(0, utility::SCREEN_WIDTH, utility::SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    texture_ = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, utility::SCREEN_WIDTH, utility::SCREEN_HEIGHT);

    SDL_SetTextureBlendMode(texture_, SDL_BLENDMODE_BLEND); // allow texture to be transparent where no pixel are used

    if (charset_ == nullptr)
    {
        printf("Err while loading charset bitmap: %s\n", SDL_GetError());
    }

    if (surface_ == nullptr)
    {
        printf("Err surface null info-bar: %s\n", SDL_GetError());
    }

    if (texture_ == nullptr)
    {
        printf("Err texture null info-bar: %s\n", SDL_GetError());
    }

    // set white key only if the charset has loaded
    if (charset_)
    {
        SDL_SetColorKey(charset_, true, 0x000000);
    }
}

InfoBar::~InfoBar()
{
    delete[] text_;
}

void InfoBar::update_timer(float dt)
{
    time_ += dt;
    sprintf(text_, "Time since started %0.fs", time_);
}

void InfoBar::update_player_health(const int player_health)
{
    player_health_ = player_health;
    sprintf(text_, "Player health %d", player_health);
}

void InfoBar::display_infobar(SDL_Renderer *renderer)
{
}

void InfoBar::update_infobar(const int player_health, const int enemy_health, float delta_time, SDL_Renderer *renderer)
{
    SDL_FillRect(surface_, NULL, 0x00000000);

    update_player_health(player_health);
    DrawingFunctions::DrawString(surface_, size_.width / 2 - strlen(text_) * 8 / 2 * scale_, 30, text_, charset_, scale_);

    update_timer(delta_time);
    DrawingFunctions::DrawString(surface_, size_.width / 2 - strlen(text_) * 8 / 2 * scale_, 50, text_, charset_, scale_);
    if (SDL_UpdateTexture(texture_, NULL, surface_->pixels, surface_->pitch))
    {
        printf("Err updating texture infobar: %s\n", SDL_GetError());
    }

    if (SDL_RenderCopy(renderer, texture_, NULL, NULL))
    {
        printf("Err fail to copy to render: %s\n", SDL_GetError());
    }

    // display everything
    display_infobar(renderer);

    printf("TIME:%f\n", time_);
}