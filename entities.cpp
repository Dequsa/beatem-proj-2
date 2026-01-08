#include "entities.h"
#include "physics.h"
#include "player.h"
#include <cstdio>

// all entity class initialization
Entity::Entity(int id, float x, float y, type_t type) : type_(type), id_(id)
{
    position_.x = x;
    position_.y = y;
}

// enemy class initialzation
Enemy::Enemy(int id, float x, float y, SDL_Renderer *screen) : health_(EnemyConstants::MAX_HEALTH),
                                                               Entity(id, x, y, type_t::ENTITY_ENEMY),
                                                               is_attacking_(false),
                                                               is_alive_(false),
                                                               attack_cd_(10)
{

    anim_.sprite_sheet = InGameManagers::LoadSpriteSheet(screen, EnemyConstants::SPRITE_PATH);

    // get sprite size
    int h = 0;
    int w = 0;
    if (SDL_QueryTexture(anim_.sprite_sheet, NULL, NULL, &w, &h))
    {
        return;
    }

    size_.height = EnemyConstants::SPRITE_HEIGHT * 0.67f;
    size_.width = EnemyConstants::SPRITE_WIDTH * 0.67f;

    printf("Enemy id: %d h:%d w: %d", id_, h, w);

    // animation initialization
    anim_.frame_duration = (1000 / utility::MONITOR_REFRESH_RATE) * 30;
    anim_.total_frames = 5;
    anim_.current_frame = 0;
    anim_.sheet_height = h;
    anim_.sheet_width = w * 0.2f; //(float)(1 / anim_.total_frames); // same as players
}

Enemy::~Enemy()
{
}

void Enemy::update_animation_sprite()
{
}

void Enemy::move()
{
}

void Enemy::attack_player(Player &p, const float dt)
{
    if (AttackFunctions::check_hitbox(position_, size_, p.get_position(), p.get_size()) && !attack_cd_)
    {
        p.recive_damage(10);
        attack_cd_ = dt * 100000;
    }
}

void Enemy::update(Player &p, const float dt)
{
    // move();
    attack_player(p, dt);

    if (attack_cd_)
        attack_cd_--;
}

// if distance between player and enemy is less or equal to screen width then enemy target player else not