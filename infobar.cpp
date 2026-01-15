#include "infobar.h"
#include "utility.h"
#include "string.h"
#include <cstdio>

InfoBar::InfoBar(position_t position, dimensions_t size) : pos_(position), size_(size)
{
    int max_lenght_string = strlen(InfoBarConstants::CONTROLS);
    text_ = new char[max_lenght_string];
    sprintf(text_, InfoBarConstants::CONTROLS);
    // load charset into mem
    charset_ = SDL_LoadBMP(InfoBarConstants::CHARSET_PATH);
    if (charset_ = nullptr)
    {
        printf("Err while loading charset bitmap: %s\n", SDL_GetError());
    }
    SDL_SetColorKey(charset_, true, 0x000000);
}

InfoBar::~InfoBar()
{
    // for now nothing
}

float InfoBar::update_timer(float dt)
{
    time_ += dt;
}

void InfoBar::display_timer(SDL_Renderer *renderer)
{
    // DrawingFunctions::DrawString(surface_, size_.width / 2 - strlen(text_) * 8 / 2, pos_.y, text_, charset_);
    // SDL_UpdateTexture(texture_, NULL, surface_->pixels, surface_->pitch);
    // SDL_RenderCopy(renderer, texture_, NULL, NULL);
}

void InfoBar::update_infobar(const float player_health, const float enemy_health, float delta_time, SDL_Renderer *renderer)
{
    // sprintf(text_, InfoBarConstants::CONTROLS);
    // update_timer(delta_time);
    // display_timer(renderer);
}