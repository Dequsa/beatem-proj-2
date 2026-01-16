#include "player.h"
#include "utility.h"
#include "entities.h"
#include <cstring>
#include <cstdio>

// Player class initialization
Player::Player(SDL_Renderer *screen) : animations_{},
                                       type_(type_t::ENTITY_PLAYER),
                                       position_{utility::SCREEN_HEIGHT / 4.0f, utility::SCREEN_WIDTH / 4.0f, 0.0f},
                                       health_(100),
                                       current_direction_(direction_t::DIRECTION_NONE),
                                       flip_state_(SDL_FLIP_NONE)
{
    name_ = new char[PlayerConstants::NAME_MAX_LENGTH]{};
    strcpy(name_, PlayerConstants::DEFAULT_NAME);

    int h = 0;
    int w = 0;
    animations_.sprite_sheet = InGameManagers::LoadTexture(screen, PlayerConstants::SPRITE_PATH, w, h);

    // // get sprite size

    // if (SDL_QueryTexture(animations_.sprite_sheet, NULL, NULL, &w, &h))
    // {
    //     printf("Error querying texture: %s\n", SDL_GetError());
    //     return;
    // }

    scale_ = PlayerConstants::SPRITE_SCALE;
    size_.height = PlayerConstants::SPRITE_HEIGHT * scale_;
    size_.width = PlayerConstants::SPRITE_WIDTH * scale_;
    offset_left_ = PlayerConstants::SPRITE_OFFSET * scale_;
    offset_right_ = 45 * scale_;

    // animation initialization
    animations_.sheet_height = h;         // frame height and width
    animations_.sheet_width = w * 0.125f; // 1 out of 8 so its 1/8th of the whole sheet's width
    animations_.frame_duration = (1000 / utility::MONITOR_REFRESH_RATE) * 30;
    animations_.total_frames = 8;
    animations_.current_frame = 0;

    // hitbox
    collision_box_ =
    {
        position_.x + (offset_left_ * scale_),
        position_.y,
        PlayerConstants::SPRITE_WIDTH * scale_, // real width
        PlayerConstants::SPRITE_HEIGHT * scale_ // real heigth
    };
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

// Update current player sprite
void Player::update_sprite_animation(const float delta_time)
{
    animations_.timer += delta_time * 1000;

    // Check if it's time to advance the frame
    if (animations_.timer >= animations_.frame_duration)
    {
        animations_.current_frame++;
        animations_.timer = 0.0f;

        // loop back to first frame if at the end
        if (animations_.current_frame >= animations_.total_frames)
        {
            animations_.current_frame = 1;
        }
    }
}

void Player::handle_controls()
{
    // get what key is pressed wihtout this lag when holding down key
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_UP]) // move up
    {
        current_direction_ = direction_t::DIRECTION_UP;
    }
    else if (state[SDL_SCANCODE_DOWN]) // move down
    {
        current_direction_ = direction_t::DIRECTION_DOWN;
    }
    else if (state[SDL_SCANCODE_LEFT]) // move left
    {
        current_direction_ = direction_t::DIRECTION_LEFT;
    }
    else if (state[SDL_SCANCODE_RIGHT]) // move right
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

void Player::update_collsion_box()
{
    collision_box_.x = position_.x + (offset_left_ * scale_);
    collision_box_.y = position_.y; // Add a top offset if needed
    collision_box_.w = PlayerConstants::SPRITE_WIDTH * scale_;
    collision_box_.h = PlayerConstants::SPRITE_HEIGHT * scale_;
}

// move player sprite on the plane based on speed delta time and direction
void Player::move(const SDL_Event &e, const float delta_time, const bool camera_state, const int map_width, const int map_heigth)
{
    handle_controls();

    speed_ = MovementFunctions::calculate_velocity(delta_time, PlayerConstants::WALKING_SPEED);

    update_flip_state();

    // move around
    MovementFunctions::move_object(speed_, position_.x, position_.y, scale_, current_direction_, size_.width, size_.height, offset_left_, offset_right_, map_width, map_heigth);

    update_collsion_box();

    MovementFunctions::bound_entity(position_, collision_box_, map_width, map_heigth);

    printf("W: %d | H: %d | X: %f | Y: %f\n", size_.width, size_.height, position_.x, position_.y);
    if (current_direction_ != direction_t::DIRECTION_NONE)
    {
        update_sprite_animation(delta_time);
    }
    else
    {
        // animations_.current_frame = 0;
        // animations_.timer = 0;
    }
}

void Player::take_damage(const int val)
{
    health_ -= val;
    printf("Health: %d\n", health_);
}