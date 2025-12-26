#pragma once
#include "utility.h"
#include "structs.h"
#include "physics.h"

class Player
{
private:
    const EntityType type_; // set to player type
    // SDL_Texture* sprite_texture_;
    char *name_;
    position_t position_;
    int current_health_;
    hitbox_t hitbox_;
    attack_t current_attack_;
    direction_t current_direction_; // 0 not moving | 1 up | 2 down | 3 left | 4 right
    SDL_RendererFlip flip_state_;
    animation_t animations;

public:
    // player class constructor
    Player();

    // player class destructor
    ~Player();

    // load player sprite
    void load_sprite(SDL_Renderer *screen);

    // update player sprite based on frame
    void update_sprite_animation(float delta_time);

    // move player sprite based on position
    int move(SDL_Event &e, float delta_time);

    // perform attack
    void attack(SDL_Event &e);

    // getters
    SDL_Texture* get_sprite_sheet() { return animations.sprite_sheet; }
    position_t get_position() { return position_; }
    direction_t direction() { return current_direction_; }
    SDL_RendererFlip get_flip_state() { return flip_state_; }
};