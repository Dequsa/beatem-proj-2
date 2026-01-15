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
    constexpr const char *SPRITE_PATH = "assets/sprites/player/player_spritesheet.bmp";
    constexpr int SPRITE_WIDTH = 195;
    constexpr int SPRITE_HEIGHT = 396;
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
    // no destructor bcs it's just a template for all entities never planing on using it to destruct using this

    // getters
    int get_id() { return id_; }
    position_t get_position() { return position_; }
    dimensions_t get_size() { return size_; }
    type_t get_type() { return type_; }
};

class Player;

class Enemy : public Entity
{
private:
    int health_;
    bool is_alive_;
    bool is_attacking_;
    float attack_cd_;
    attack_t current_attack_;
    animation_t anim_;
    SDL_RendererFlip flip_;

    // sprite handling
    void update_animation_sprite();

    // movement
    void move();

    //attacks
    void choose_attack();
    void attack_player(Player &p, const float dt);

public:
    Enemy(int id, float x, float y, SDL_Renderer *screen);
    ~Enemy();

    void update(Player &p, const float dt);

    // getters
    animation_t get_animation() { return anim_; };
    SDL_Texture *get_sprite_sheet() { return anim_.sprite_sheet; };
    SDL_RendererFlip GetFlipState() { return flip_; };
};

class StaticObject : public Entity
{
private:
    position_t pos_;
    dimensions_t size_;
public:
    StaticObject();
    ~StaticObject();
};
