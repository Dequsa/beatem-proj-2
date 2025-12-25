#pragma once

#include "utility.h"
#include "structs.h"
class Player
{
private:
    const EntityType type_; // set to player type
    SDL_Surface *sprite_surface_;
    char *name_;
    position_t position_;
    int current_health_;
    hitbox_t hitbox_;
    attack_t current_attack_;
    int current_key_event_;

public:
    // player class constructor
    Player();

    // player class destructor
    ~Player();
    
    // update player sprite based on position
    void sprite_update();

    // move player sprite based on position
    int move(SDL_Event &e);

    // perform attack
    void attack(SDL_Event &e);

    // getters
    SDL_Surface* get_sprite_surface() { return sprite_surface_; }
    position_t get_position() { return position_; }
};