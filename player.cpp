#include "player.h"
#include "utility.h"
#include "entities.h"
#include <cstring>

// Player class constructor
Player::Player() : sprite_surface_(nullptr),
                   type_(EntityType::ENTITY_PLAYER),
                   position_{50.0f, 30.0f, 0.0f},
                   current_health_(100),
                   hitbox_{-16.0f, -16.0f, {32.0f, 32.0f}},
                   current_attack_{0, 10, 0, 0},
                   current_key_event_(-1)
{
    name_ = new char[utility::PLAYER_NAME_MAX_LENGTH]{};
    strcpy(name_, "Brawler");

    // load player sprite
    sprite_surface_ = SDL_LoadBMP("assets/sprites/sprite_player.bmp");
}

// Player class destructor
Player::~Player()
{
    if (name_ != nullptr)
    {
        delete[] name_;
        name_ = nullptr;
    }
}

// update player sprite based on position
void Player::sprite_update()
{
}

// move player sprite based on position
int Player::move(SDL_Event &e)
{
    current_key_event_ = e.key.keysym.sym;
    switch (current_key_event_)
    {
    case SDLK_UP:
        position_.y -= 10.0f;
        break;
    case SDLK_DOWN:
        position_.y += 10.0f;
        break;
    case SDLK_LEFT:
        position_.x -= 10.0f;
        break;
    case SDLK_RIGHT:
        position_.x += 10.0f;
        break;
    case SDLK_ESCAPE:
        return -1;
    }

    return 0;
}