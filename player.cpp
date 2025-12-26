#include "player.h"
#include "utility.h"
#include "entities.h"
#include <cstring>
#include <cstdio>

// Player class constructor
Player::Player() : animations{nullptr, 64, 64, 8, 0, 100.0f, 0.0f},
                   type_(EntityType::ENTITY_PLAYER),
                   position_{utility::SCREEN_HEIGHT / 2.0f, utility::SCREEN_WIDTH / 2.0f, 0.0f},
                   current_health_(100),
                   hitbox_{-16.0f, -16.0f, {32.0f, 32.0f}},
                   current_attack_{0, 10, 0, 0},
                   current_direction_(direction_t::DIRECTION_NONE),
                   flip_state_(SDL_FLIP_NONE)
{
    name_ = new char[utility::PLAYER_NAME_MAX_LENGTH]{};
    strcpy(name_, "Brawler");
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

// update player sprite based on frame
void Player::load_sprite(SDL_Renderer *screen)
{
    // load player sprite
    SDL_Surface *temp_surface = SDL_LoadBMP("assets/sprites/player/player_spritesheet.bmp");

    if (temp_surface == nullptr)
    {
        printf("err while loading player sprite : %s \n", SDL_GetError());
    }
    else
    {
        animations.sprite_sheet = SDL_CreateTextureFromSurface(screen, temp_surface);
    }
}

void Player::update_sprite_animation(float delta_time)
{
    // Update animation timer
    animations.timer += delta_time * 1000; // convert to milliseconds

    // Check if it's time to advance the frame
    if (animations.timer >= animations.frame_duration)
    {
        animations.current_frame++;
        animations.timer = 0.0f;

        // loop back to first frame if at the end
        if (animations.current_frame >= animations.total_frames)
        {
            animations.current_frame = 0;
        }
    }
}

// move player sprite based on position
int Player::move(SDL_Event &e, float delta_time)
{
    const Uint8 *current_key_state = SDL_GetKeyboardState(NULL);
    const int speed = utility::PLAYER_SPEED_WALKING * delta_time * 1000; // scale speed by delta_time

    if (current_key_state[SDL_SCANCODE_UP])
    {
        position_.y -= speed;
    }
    else if (current_key_state[SDL_SCANCODE_DOWN])
    {
        position_.y += speed;
    }
    else if (current_key_state[SDL_SCANCODE_LEFT])
    {
        position_.x -= speed;
        flip_state_ = SDL_FLIP_HORIZONTAL;
    }
    else if (current_key_state[SDL_SCANCODE_RIGHT])
    {
        position_.x += speed;
        flip_state_ = SDL_FLIP_NONE;
    }

    return 0;
}