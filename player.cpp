#include "player.h"
#include "utility.h"
#include "entities.h"
#include <cstring>
#include <cstdio>

// Player class initialization
Player::Player(SDL_Renderer *screen) : animations{nullptr, 64, 64, 8, 0, 100.0f, 0.0f},
                                       type_(enitity_type::ENTITY_PLAYER),
                                       position_{utility::SCREEN_HEIGHT / 2.0f, utility::SCREEN_WIDTH / 2.0f, 0.0f},
                                       current_health_(100),
                                       hitbox_{-16.0f, -16.0f, {32.0f, 32.0f}},
                                       current_attack_{0, 10, 0, 0},
                                       current_direction_(direction_t::DIRECTION_NONE),
                                       flip_state_(SDL_FLIP_NONE)
{
    name_ = new char[player_constants::NAME_MAX_LENGTH]{};
    strcpy(name_, "Brawler");

    SDL_Surface *temp_surface = SDL_LoadBMP(player_constants::SPRITE_PATH);

    if (temp_surface == nullptr)
    {
        printf("err while loading player sprite : %s \n", SDL_GetError());
    }
    else
    {
        // create texture from surface
        animations.sprite_sheet = SDL_CreateTextureFromSurface(screen, temp_surface);
    }

    // free temp surface
    SDL_FreeSurface(temp_surface);
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


// NEED TO CHANGE TH BOUNDING MECHANISIM
// move player sprite based on speed delta time and direction
int Player::move(SDL_Event &e, float delta_time)
{
    const Uint8 *current_key_state = SDL_GetKeyboardState(NULL);
    speed_ = player_constants::SPEED_WALKING * delta_time * 1000.0f; // scale speed by delta_time

    if (current_key_state[SDL_SCANCODE_UP]) // move up
    {
        if (position_.y - speed_ < 471 * 0.68f) // prevent moving off screen 471 * background_size_ratio
            position_.y = 471 * 0.68f;
        else
            position_.y -= speed_;
    }
    else if (current_key_state[SDL_SCANCODE_DOWN]) // move down
    {
        if (position_.y + player_constants::SPRITE_HEIGHT * scale_ + speed_ > utility::SCREEN_HEIGHT) // prevent moving off screen
            position_.y = utility::SCREEN_HEIGHT - player_constants::SPRITE_HEIGHT * scale_;
        else
            position_.y += speed_;
    }
    else if (current_key_state[SDL_SCANCODE_LEFT]) // move left
    {
        if (position_.x - speed_ < 0) // prevent moving off screen
            position_.x = 0;
        else
            position_.x -= speed_;

        flip_state_ = SDL_FLIP_HORIZONTAL;
    }
    else if (current_key_state[SDL_SCANCODE_RIGHT]) // move right
    {
        if (position_.x + player_constants::SPRITE_WIDTH * scale_ + speed_ > utility::SCREEN_WIDTH) // prevent moving off screen
            position_.x = utility::SCREEN_WIDTH - player_constants::SPRITE_WIDTH * scale_;
        else
            position_.x += speed_;

        flip_state_ = SDL_FLIP_NONE;
    }

    return 0;
}