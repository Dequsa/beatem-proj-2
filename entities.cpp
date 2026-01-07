#include "entities.h"
#include "physics.h"
#include <cstdio>

// all entity class initialization
Entity::Entity(int id, float x, float y, type_t type) : type_(type)
{
    position_.x = x;
    position_.y = y;
}

// enemy class initialzation
Enemy::Enemy(int id, float x, float y, SDL_Renderer *screen) : health_(EnemyConstants::MAX_HEALTH), Entity(id, x, y, type_t::ENTITY_ENEMY)
{

    anim_.sprite_sheet = InGameManagers::LoadSpriteSheet(screen, EnemyConstants::SPRITE_PATH);

    // get sprite size
    int h = 0;
    int w = 0;
    if (SDL_QueryTexture(anim_.sprite_sheet, NULL, NULL, &w, &h))
    {
        return;
    }

    size_.height = h;
    size_.width = w;

    printf("h:%d w: %d",h,w);

    // animation initialization
    anim_.frame_height = h;
    anim_.frame_width = 0.2f * w;
    anim_.frame_duration = (1000 / utility::MONITOR_REFRESH_RATE) * 30;
    anim_.total_frames = 5;
    anim_.current_frame = 0;
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

void Enemy::damage_player()
{
}

void Enemy::update(position_t player_pos, dimensions_t player_size, float dt)
{
    move();
    
    if (MovementFunctions::check_hitbox(position_, size_, player_pos, player_size))
    {
        printf("Hit box colliding.");
        damage_player();
    }
}