#pragma once
#include "utility.h"
#include "structs.h"
#include "physics.h"

namespace PlayerConstants
{
    constexpr float WALKING_SPEED = 1.0f;
    constexpr float RUNNING_SPEED = 3.0f;
    constexpr int NAME_MAX_LENGTH = 128;
    constexpr char* SPRITE_PATH = "assets/sprites/player/sprite_player_1.bmp";
    constexpr int SPRITE_WIDTH = 659;
    constexpr int SPRITE_HEIGHT = 1324;
}

class Player
{
private:
    const enitity_t type_; // set to player type
    char *name_;
    position_t position_;
    int current_health_;
    float scale_ = 0.3f;
    hitbox_t hitbox_;
    attack_t current_attack_;
    direction_t current_direction_; // 0 not moving | 1 up | 2 down | 3 left | 4 right
    SDL_RendererFlip flip_state_;
    animation_t animations;
    float speed_;
    dimensions_t size_;

    // handle player controls / key-state
    void handle_controls();

    // flips player
    void update_flip_state();

    // clamp by right left
    void bound_sides(int map_width);
    
    // clamp by top bottom
    void bound_top(int map_heigth);

public:
    // player class constructor
    Player(SDL_Renderer *screen);

    // player class destructor
    ~Player();

    // update player sprite based on frame
    void update_sprite_animation(float delta_time);

    // move player sprite based on position
    void move(SDL_Event &e, float delta_time, bool camera_state, int map_width, int map_heigth);

    // perform attack
    void attack(SDL_Event &e);

    // getters
    SDL_Texture* get_sprite_sheet() { return animations.sprite_sheet; }
    position_t get_position() { return position_; }
    direction_t get_direction() { return current_direction_; }
    SDL_RendererFlip get_flip_state() { return flip_state_; }
    float get_scale() { return (position_.z / utility::SCREEN_HEIGHT); }
    float get_speed() { return speed_; }
    dimensions_t get_size() { return size_; }
};