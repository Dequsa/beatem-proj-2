#include "entities.h"

// all entity class initialization
Entity::Entity(int id, float x, float y, type_t type) : type_(type)
{
    position_.x = x;
    position_.y = y;
}

// enemy class initialzation
Enemy::Enemy(int id, float x, float y, SDL_Renderer *screen) : Entity(id ,x, y, type_t::ENTITY_ENEMY),
                                        health_(EnemyConstants::MAX_HEALTH)
{
    anim_.total_frames = EnemyConstants::TOTAL_FRAMES_ANIM;
    anim_.frame_duration = (1000 / utility::MONITOR_REFRESH_RATE) * 30;
    anim_.frame_height = 10.0f;
    anim_.frame_width = 10.0f;
    anim_.sprite_sheet = InGameLoaders::LoadSpriteSheet(screen, EnemyConstants::SPRITE_PATH);
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