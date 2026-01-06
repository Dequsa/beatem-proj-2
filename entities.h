#pragma once
#include "structs.h"
#include "utility.h"

namespace StaticObjectConstants
{
    
}

namespace EnemyConstants
{
    constexpr int MAX_HEALTH = 100;
    constexpr int TOTAL_FRAMES_ANIM = 5;
    constexpr char *SPRITE_PATH = "assets/sprites/player/player_spritesheet.bmp";
}

class Entity
{
protected:
    int id_;
    position_t position_;
    dimensions_t size_;
    type_t type_;

public:
    Entity(int id, float x, float y, type_t type);
    virtual ~Entity(){};

    // getters
    int get_id() { return id_; }
    position_t get_position() { return position_; }
    dimensions_t get_size() { return size_; }
    type_t get_type() { return type_; }
};

class Enemy : public Entity
{
private:
    int health_;
    bool is_alive_;
    attack_t current_attack_;
    animation_t anim_;

    void update_animation_sprite();
    void move();
    void damage_player();

public:
    Enemy(int id, float x, float y, SDL_Renderer *screen);
    ~Enemy();

    void update();
};

class StaticObject : public Entity
{
private:
public:
    StaticObject();
    ~StaticObject();
};
