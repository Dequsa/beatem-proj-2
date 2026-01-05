#include "player.h"
#include "utility.h"
#include "entities.h"
#include <cstring>
#include <cstdio>

// Player class initialization
Player::Player(SDL_Renderer *screen) : animations{nullptr, 64, 64, 8, 0, 100.0f, 0.0f},
                                       type_(enitity_t::ENTITY_PLAYER),
                                       position_{utility::SCREEN_HEIGHT / 4.0f, utility::SCREEN_WIDTH / 4.0f, 0.0f},
                                       current_health_(100),
                                       hitbox_{-16.0f, -16.0f, {32.0f, 32.0f}},
                                       current_attack_{0, 10, 0, 0},
                                       current_direction_(direction_t::DIRECTION_NONE),
                                       flip_state_(SDL_FLIP_NONE)
{
    name_ = new char[PlayerConstants::NAME_MAX_LENGTH]{};
    strcpy(name_, "Brawler");

    SDL_Surface *temp_surface = SDL_LoadBMP(PlayerConstants::SPRITE_PATH);

    if (temp_surface == nullptr)
    {
        printf("err while loading player sprite : %s \n", SDL_GetError());
    }
    else
    {
        // create texture from surface
        animations.sprite_sheet = SDL_CreateTextureFromSurface(screen, temp_surface);
    }

    // get sprite size
    int h = 0;
    int w = 0;
    if (SDL_QueryTexture(animations.sprite_sheet, NULL, NULL, &w, &h))
    {
        printf("Error querying texture: %s\n", SDL_GetError());
        return;
    }

    size_.height = h * 0.2f;
    size_.width = w * 0.2f;

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

void Player::handle_controls()
{
    const Uint8 *current_key_state = SDL_GetKeyboardState(NULL);

    if (current_key_state[SDL_SCANCODE_UP]) // move up
    {
        current_direction_ = direction_t::DIRECTION_UP;
    }
    else if (current_key_state[SDL_SCANCODE_DOWN]) // move down
    {
        current_direction_ = direction_t::DIRECTION_DOWN;
    }
    else if (current_key_state[SDL_SCANCODE_LEFT]) // move left
    {
        current_direction_ = direction_t::DIRECTION_LEFT;
    }
    else if (current_key_state[SDL_SCANCODE_RIGHT]) // move right
    {
        current_direction_ = direction_t::DIRECTION_RIGHT;
    }
    else
    {
        current_direction_ = direction_t::DIRECTION_NONE;
    }
}

void Player::update_flip_state()
{
    switch (current_direction_)
    {
    case direction_t::DIRECTION_LEFT:
        flip_state_ = SDL_FLIP_HORIZONTAL;
        break;
    case direction_t::DIRECTION_RIGHT:
        flip_state_ = SDL_FLIP_NONE;
        break;
    }
}

void Player::bound_sides(int map_width)
{
    if (position_.x + size_.width > map_width)
        position_.x = map_width - size_.width;

    if (position_.x < 0.0f)
        position_.x = 0.0f;
}

void Player::bound_top(int map_heigth)
{

    if (position_.y < 1063.0f - size_.height)
        position_.y = 1063.0f - size_.height;

    if (position_.y > map_heigth - size_.height)
        position_.y = map_heigth - size_.height;
}

// move player sprite on the plane based on speed delta time and direction
void Player::move(SDL_Event &e, float delta_time, bool camera_state, int map_width, int map_heigth)
{
    handle_controls();

    speed_ = PhysicsFunctions::calculate_velocity(delta_time, PlayerConstants::WALKING_SPEED);

    update_flip_state();

    bound_sides(map_width);
    bound_top(map_heigth);

    PhysicsFunctions::move_object_y(speed_, &position_.x, &position_.y, current_direction_);
    PhysicsFunctions::move_object_x(speed_, &position_.x, &position_.y, current_direction_);
}