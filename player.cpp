#include "player.h"
#include "utility.h"
#include "entities.h"
#include <cstring>
#include <cstdio>

// Player class initialization
Player::Player(SDL_Renderer *screen) : animations_{},
                                       type_(type_t::ENTITY_PLAYER),
                                       position_(PlayerConstants::spawn_point),
                                       health_(100),
                                       current_direction_(direction_t::DIRECTION_NONE),
                                       flip_state_(SDL_FLIP_NONE),
                                       is_attacking_(false),
                                       is_dashing_(false),
                                       dash_strength(4.5f),
                                       has_attacked_(false)
{
    name_ = new char[PlayerConstants::NAME_MAX_LENGTH]{};
    strcpy(name_, PlayerConstants::DEFAULT_NAME);

    // hitbox size
    scale_ = PlayerConstants::SPRITE_SCALE;
    size_.height = PlayerConstants::SPRITE_HEIGHT * scale_;
    size_.width = PlayerConstants::SPRITE_WIDTH * scale_;

    // animation initialization
    animations_.sprite_sheet = InGameManagers::LoadSpriteSheet(screen, PlayerConstants::SPRITE_PATH, nullptr, nullptr);

    animations_.total_frames = new int[PlayerConstants::ANIMATION_COUNT];

    animations_.size.height = PlayerConstants::SPRITE_HEIGHT;
    animations_.size.width = PlayerConstants::SPRITE_WIDTH;

    animations_.frame_duration = (1000 / utility::MONITOR_REFRESH_RATE) * 10;
    animations_.current_frame = 0;
    animations_.current_action = ActionSheet::walk_up;

    for (int i = 0; i < PlayerConstants::ANIMATION_COUNT; ++i)
    {
        animations_.total_frames[i] = 1; // so it not crash
    }

    for (int i = 0; i < 4; ++i)
    {
        animations_.total_frames[static_cast<int>(ActionSheet::walk_up) + i] = 8;
        animations_.total_frames[static_cast<int>(ActionSheet::slash_up) + i] = 6;
        animations_.total_frames[static_cast<int>(ActionSheet::thrust_up) + i] = 8;
    }
}

// Player class destructor
Player::~Player()
{
    if (name_ != nullptr)
    {
        delete[] name_;
        name_ = nullptr;
    }
    // free animations stuff
    if (animations_.total_frames != nullptr)
    {
        delete[] animations_.total_frames;
        animations_.total_frames = nullptr;
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
        if (animations_.current_frame >= animations_.total_frames[static_cast<int>(animations_.current_action)])
        {
            animations_.current_frame = 0;
        }
    }
}

void Player::choose_dash_direction()
{
    switch (last_direction_)
    {
    case direction_t::DIRECTION_UP:
        animations_.current_action = ActionSheet::thrust_up; // 26
        break;
    case direction_t::DIRECTION_LEFT:
        animations_.current_action = ActionSheet::thrust_left;
        break;
    case direction_t::DIRECTION_DOWN:
        animations_.current_action = ActionSheet::thrust_down;
        break;
    case direction_t::DIRECTION_RIGHT:
        animations_.current_action = ActionSheet::thrust_right;
        break;
    }

    animations_.current_frame = 0;
    animations_.timer = 0.0f;
}

void Player::choose_direction_light_attack()
{
    switch (last_direction_)
    {
    case direction_t::DIRECTION_UP:
        animations_.current_action = ActionSheet::slash_up;
        break;
    case direction_t::DIRECTION_LEFT:
        animations_.current_action = ActionSheet::slash_left;
        break;
    case direction_t::DIRECTION_DOWN:
        animations_.current_action = ActionSheet::slash_down;
        break;
    case direction_t::DIRECTION_RIGHT:
        animations_.current_action = ActionSheet::slash_right;
        break;
    }

    // reset animation so it doesnt snap or play only half
    animations_.current_frame = 0;
    animations_.timer = 0.0f;
}

void Player::choose_direction_heavy_attack()
{
    switch (last_direction_)
    {
    case direction_t::DIRECTION_UP:
        animations_.current_action = ActionSheet::slash_up;
        break;
    case direction_t::DIRECTION_LEFT:
        animations_.current_action = ActionSheet::slash_left;
        break;
    case direction_t::DIRECTION_DOWN:
        animations_.current_action = ActionSheet::slash_down;
        break;
    case direction_t::DIRECTION_RIGHT:
        animations_.current_action = ActionSheet::slash_right;
        break;
    }

    // reset animation so it doesnt snap or play only half
    animations_.current_frame = 0;
    animations_.timer = 0.0f;
}

void Player::set_light_attack()
{
    is_attacking_ = true;
    current_attack_ = Attacks::LIGHT;

    choose_direction_light_attack();

    if (utility::DEBUG_MODE)
    {
        printf("%s\n", current_attack_.name);
    }
}

void Player::set_heavy_attack()
{
    is_attacking_ = true;
    current_attack_ = Attacks::HEAVY;

    choose_direction_heavy_attack();

    if (utility::DEBUG_MODE)
    {
        printf("%s\n", current_attack_.name);
    }
}

void Player::count_attack_cooldown(float dt)
{
    if (current_attack_.cooldown >= 0)
    {
        current_attack_.cooldown -= dt;
    }
}

void Player::handle_controls()
{

    // attacking
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (!is_dashing_ && !is_attacking_ && current_attack_.cooldown <= 0)
    {
        if (state[SDL_SCANCODE_Z]) // light attack
        {
            set_light_attack();
        }
        else if (state[SDL_SCANCODE_X]) // heavy attack
        {
            set_heavy_attack();
        }
    }

    // dashing
    if (!is_attacking_ && !is_dashing_ && current_attack_.cooldown <= 0)
    {
        if (state[SDL_SCANCODE_SPACE])
        {
            current_attack_.cooldown = -1;
            is_dashing_ = true;
            choose_dash_direction();
        }
    }

    // walking
    if (!is_dashing_ && !is_attacking_)
    {
        if (state[SDL_SCANCODE_UP]) // move up
        {
            current_direction_ = direction_t::DIRECTION_UP;
            last_direction_ = current_direction_;
            animations_.current_action = ActionSheet::walk_up;
        }
        else if (state[SDL_SCANCODE_DOWN]) // move down
        {
            current_direction_ = direction_t::DIRECTION_DOWN;
            last_direction_ = current_direction_;
            animations_.current_action = ActionSheet::walk_down;
        }
        else if (state[SDL_SCANCODE_LEFT]) // move left
        {
            current_direction_ = direction_t::DIRECTION_LEFT;
            last_direction_ = current_direction_;
            animations_.current_action = ActionSheet::walk_left;
        }
        else if (state[SDL_SCANCODE_RIGHT]) // move right
        {
            current_direction_ = direction_t::DIRECTION_RIGHT;
            last_direction_ = current_direction_;
            animations_.current_action = ActionSheet::walk_right;
        }
        else
        {
            current_direction_ = direction_t::DIRECTION_NONE;
        }
    }
}

bool Player::has_animation_ended()
{
    return animations_.timer <= 0.0f && animations_.current_frame == 0;
}

// move player sprite on the plane based on speed delta time and direction
void Player::move(const SDL_Event &e, const float delta_time, const bool camera_state, const int map_width, const int map_heigth, Enemy &enemy)
{
    count_attack_cooldown(delta_time);
    handle_controls();

    if (current_direction_ != direction_t::DIRECTION_NONE || is_attacking_ || is_dashing_)
    {
        update_sprite_animation(delta_time);
    }
    else
    {
        animations_.current_frame = 0;
    }

    if (is_attacking_)
    {
        if (AttackFunctions::check_hitbox(position_, size_, enemy.get_position(), enemy.get_size()) && !has_attacked_)
        {
            has_attacked_ = true;
            enemy.recive_damage(current_attack_.dmg);
        }

        if (has_animation_ended())
        {
            is_attacking_ = false;
            has_attacked_ = false;
        }

        return;
    }

    if (is_dashing_)
    {

        if (animations_.current_frame > 2)
        {
            MovementFunctions::dash(last_direction_, position_, size_, map_width, map_heigth, scale_, dash_strength);

            if (AttackFunctions::check_hitbox(position_, size_, enemy.get_position(), enemy.get_size()) && !has_attacked_)
            {
                has_attacked_ = true;
                current_attack_ = Attacks::DASH;
                enemy.recive_damage(current_attack_.dmg);
            }
        }

        if (has_animation_ended())
        {
            is_dashing_ = false;
            has_attacked_ = false;
        }

        return;
    }

    speed_ = MovementFunctions::calculate_velocity(delta_time, PlayerConstants::WALKING_SPEED);

    MovementFunctions::move_object(speed_, position_.x, position_.y, scale_, current_direction_, size_.width, size_.height, map_width, map_heigth);
}

void Player::take_damage(const int val)
{
    health_ -= val;

    if (utility::DEBUG_MODE)
    {
        printf("Player Health: %d\n", health_);
    }
}