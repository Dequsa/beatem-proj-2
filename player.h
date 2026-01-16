#pragma once
#include "utility.h"
#include "structs.h"
#include "physics.h"

namespace PlayerConstants
{
    constexpr const char *DEFAULT_NAME = "Brawler";
    constexpr float WALKING_SPEED = 1.0f;
    constexpr float RUNNING_SPEED = 3.0f;
    constexpr int NAME_MAX_LENGTH = 128;
    constexpr const char *SPRITE_PATH = "assets/sprites/player/Walk.bmp";
    constexpr int SPRITE_WIDTH = 35;
    constexpr int SPRITE_HEIGHT = 85;
    constexpr int SPRITE_OFFSET = 45;
    constexpr float SPRITE_SCALE = 3.0f; // 0.67f;
}

class Player
{
private:
    type_t type_; // set to player type
    char *name_;
    position_t position_;
    int health_;
    attack_t current_attack_;
    direction_t current_direction_; // 0 not moving | 1 up | 2 down | 3 left | 4 right
    SDL_RendererFlip flip_state_;
    animation_t animations_;
    float speed_;
    dimensions_t size_;
    float scale_;
    float offset_left_, offset_right_;
    SDL_FRect collision_box_;

    // handle player controls / key-state
    void handle_controls();

    // flips player
    void update_flip_state();

    // // clamp by right left
    // void bound_sides(int map_width);

    // // clamp by top bottom
    // void bound_top(int map_heigth);

public:
    // player class constructor
    Player(SDL_Renderer *screen);

    // player class destructor
    ~Player();

    // update player sprite based on frame
    void update_sprite_animation(const float delta_time);

    // update hitbox position
    void update_collsion_box();

    // move player sprite based on position
    void move(const SDL_Event &e, const float delta_time, const bool camera_state, const int map_width, const int map_heigth);

    // setters:

    void take_damage(const int val);

    // getters:
    SDL_Texture *get_sprite_sheet() { return animations_.sprite_sheet; }
    position_t get_position() { return position_; }
    direction_t get_direction() { return current_direction_; }
    SDL_RendererFlip get_flip_state() { return flip_state_; }
    float get_scale() { return scale_; }
    float get_speed() { return speed_; }
    dimensions_t get_size() { return size_; }
    animation_t get_animation() { return animations_; }
    float get_offset_left() { return offset_left_; }
    SDL_FRect get_collision_box() { return collision_box_; }
};