#pragma once
#include "utility.h"
#include "structs.h"
#include "physics.h"

class Enemy;


namespace PlayerConstants
{
    constexpr const char* DEFAULT_NAME = "Brawler";
    constexpr float WALKING_SPEED = 0.6f;
    constexpr float RUNNING_SPEED = 3.0f;
    constexpr int NAME_MAX_LENGTH = 128;
    constexpr const char* SPRITE_PATH = "assets/sprites/player/character-spritesheet.bmp";
    constexpr int SPRITE_WIDTH = 64;
    constexpr int SPRITE_HEIGHT = 64;
    constexpr float SPRITE_SCALE = 5.0f;
    constexpr int ANIMATION_COUNT = 64;
    constexpr position_t spawn_point = {200.0f, 1200.0f};
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
    direction_t last_direction_;    // 0 not moving | 1 up | 2 down | 3 left | 4 right
    SDL_RendererFlip flip_state_;
    animation_t animations_;
    float speed_;
    dimensions_t size_;
    float scale_;
    bool is_attacking_;
    bool is_dashing_;
    float dash_strength;
    bool has_attacked_;

    //utility checks
    bool has_animation_ended();

    // handle player controls / key-state
    void handle_controls();

    // which way to dash
    void choose_dash_direction();

    // which way to attack
    void choose_direction_light_attack();
    void choose_direction_heavy_attack();

    // set attack
    void set_light_attack();
    void set_heavy_attack();

    void count_attack_cooldown(float dt);

public:
    // player class constructor
    Player(SDL_Renderer *screen);

    // player class destructor
    ~Player();

    // update player sprite based on frame
    void update_sprite_animation(const float delta_time);

    // move player sprite based on position
    void move(const SDL_Event &e, const float delta_time, const bool camera_state, const int map_width, const int map_heigth, Enemy &enemy);

    // setters:
    
    void take_damage(const int val);
    
    // getters:
    int get_health() { return health_; }
    SDL_Texture* get_sprite_sheet() { return animations_.sprite_sheet; }
    position_t get_position() { return position_; }
    direction_t get_direction() { return current_direction_; }
    SDL_RendererFlip get_flip_state() { return flip_state_; }
    float get_scale() { return scale_; }
    float get_speed() { return speed_; }
    dimensions_t get_size() { return size_; }
    animation_t get_animation() { return animations_; }
    ActionSheet get_current_action() { return animations_.current_action; }
};

