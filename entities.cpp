#include "entities.h"
#include "physics.h"
#include "player.h"
#include <cstdio>
#include <cmath>
#include <ctime>

// all entity class initialization
Entity::Entity(int id, float x, float y, type_t type) : type_(type), id_(id)
{
    position_.x = x;
    position_.y = y;
}

// enemy class initialzation
Enemy::Enemy(int id, float x, float y, SDL_Renderer *screen) : Entity(id, x, y, type_t::ENTITY_ENEMY),
                                                               health_(EnemyConstants::MAX_HEALTH),
                                                               is_attacking_(false),
                                                               is_alive_(false),
                                                               attack_cd_(1.0f),
                                                               flip_(SDL_FLIP_NONE)
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
    if (position_.x <= utility::SCREEN_WIDTH)
    {
        flip_ = SDL_FLIP_NONE;
        position_.x += 0.1f;
    }
    else
    {
        flip_ = SDL_FLIP_HORIZONTAL;
        position_.x -= 0.1f;
    }
}

void Enemy::choose_attack()
{
    srand(time(nullptr));
    int random_attack = rand() % static_cast<int>(Attacks::Number::Count);

    switch (random_attack)
    {
    case static_cast<int>(Attacks::Number::LIGHT):
        current_attack_ = Attacks::LIGHT;
        break;

    case static_cast<int>(Attacks::Number::HEAVY):
        current_attack_ = Attacks::HEAVY;
        break;
    }
}

void Enemy::attack_player(Player &p, const float dt)
{
    if (AttackFunctions::check_hitbox(position_, size_, p.get_position(), p.get_size()) && (attack_cd_ <= 0))
    {
        choose_attack();

        if (utility::DEBUG_MODE)
        {
            printf("Current attack: %s | Dmg: %d | Cooldown set to: %f\n", current_attack_.name, current_attack_.dmg, current_attack_.cooldown);
        }

        p.take_damage(current_attack_.dmg);
        attack_cd_ = current_attack_.cooldown;
    }
}

void Enemy::update(Player &p, const float dt)
{
    // move();
    attack_player(p, dt);
    move();

    if (utility::DEBUG_MODE)
    {
        printf("Cooldown: %f\n", attack_cd_);
    }

    if (attack_cd_ > 0)
        attack_cd_ -= dt;
}

// if distance between player and enemy is less or equal to screen width then enemy target player else not