#include "physics.h"
#include "camera.h"
#include <cmath>
#include <cstdio>

namespace MovementFunctions
{
    // bounding system

    void bound_entity(float &x, float &y, int w, int h, int map_w, int map_h)
    {
        // bound x
        if (x + w > map_w) // right side of the map
            x = map_w - w;

        if (x < 0.0f) // left side
            x = 0.0f;

        // bound y
        if (y < 1163.0f - h) // floor top
            y = 1163.0f - h;

        if (y > map_h - h) // bottom of the screen
            y = map_h - h;
    }

    // calculating velocity
    float calculate_velocity(float dt, float base_vel)
    {
        return (float)(base_vel * dt * 1000.0f); // scale speed by delta_time
    }

    // moving system
    void move_object_x(float velocity, float &x, float &y, direction_t current_direction)
    {
        switch (current_direction)
        {
        case direction_t::DIRECTION_LEFT:
            x -= velocity;
            break;
        case direction_t::DIRECTION_RIGHT:
            x += velocity;
            break;
        default:
            return;
        }
    }

    void move_object_y(float velocity, float &x, float &y, float &scale, direction_t current_direction)
    {
        float min_size = 0.51f;
        float max_size = 0.67f;
        float distance = 200.0f * CameraConstants::BACKGROUND_SIZE_RATIO;
        float scale_step = (max_size - min_size) / distance;

        switch (current_direction)
        {
        case direction_t::DIRECTION_UP:
            y -= velocity;
           
            scale -= scale_step;
            
            if (scale <= min_size)
            {
                scale = min_size;
            }
            break;
        case direction_t::DIRECTION_DOWN:
            y += velocity;
           
            scale += scale_step;

            if (scale >= max_size)
            {
                scale = max_size;
            }
            break;
        default:
            return;
        }
    }

    void move_object(float velocity, float &x, float &y, float &scale, direction_t current_direction, int w, int h, int map_w, int map_h)
    {
        if (current_direction == direction_t::DIRECTION_NONE)
        {
            return;
        }

        move_object_x(velocity, x, y, current_direction);
        move_object_y(velocity, x, y, scale, current_direction);
        bound_entity(x, y, w, h, map_w, map_h);
    }
}

namespace AttackFunctions
{
    // attack system
    bool check_hitbox(position_t pos_1, dimensions_t size_1, position_t pos_2, dimensions_t size_2)
    {
        bool in_range = false;

        if (pos_1.x < pos_2.x + size_2.width && pos_1.x + size_1.width > pos_2.x && pos_1.y < pos_2.y + size_2.height && pos_1.y + size_1.height > pos_2.y) // rectangle check
        {
            in_range = true;
        }

        if (utility::DEBUG_MODE)
        {
            printf("%d\n", in_range);
        }

        return in_range;
    }

    void attack(int &target_helth, float &source_cooldown, attack_t attack_move)
    {
        target_helth -= attack_move.dmg;
        source_cooldown = attack_move.cooldown;

        printf("Attack: %s\n", attack_move.name);
    }
}