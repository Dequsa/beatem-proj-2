#include "physics.h"
#include <cmath>
#include <cstdio>

namespace MovementFunctions
{
    // collision system

    // bounding system

    // hitting system

    // calculating velocity
    float calculate_velocity(float dt, float base_vel)
    {
        return (float)(base_vel * dt * 1000.0f); // scale speed by delta_time
    }

    // moving system
    void move_object_x(float velocity, float *x, float *y, direction_t current_direction)
    {
        switch (current_direction)
        {
        case direction_t::DIRECTION_LEFT:
            *x -= velocity;
            break;
        case direction_t::DIRECTION_RIGHT:
            *x += velocity;
            break;
        default:
            return;
        }
    }

    void move_object_y(float velocity, float *x, float *y, direction_t current_direction)
    {
        switch (current_direction)
        {
        case direction_t::DIRECTION_UP:
            *y -= velocity;
            break;
        case direction_t::DIRECTION_DOWN:
            *y += velocity;
            break;
        default:
            return;
        }
    }

    void move_object(float velocity, float *x, float *y, direction_t current_direction)
    {
        if (current_direction == direction_t::DIRECTION_NONE)
            return;

        move_object_x(velocity, x, y, current_direction);
        move_object_y(velocity, x, y, current_direction);
    }

    bool check_hitbox(position_t pos_1, dimensions_t size_1, position_t pos_2, dimensions_t size_2)
    {
        bool can_attack = false;
        float d_x = pos_1.x - pos_2.x;
        float d_y = pos_1.y - pos_2.y;
        float d = sqrt(d_x * d_x + d_y * d_y);

        //printf("d_x: %f | d_y: %f | d: %f | size_2.w: %d | size_2.h: %d | size_1.w: %d | size_1.h: %d\n", d_x, d_y, d, size_2.width, size_2.height, size_1.width, size_1.width);

        // float d_2 = sqrt(size_2.width * size_2.width + size_2.height * size_2.height);
        // float d_1 = sqrt(size_1.width * size_1.width + size_1.height * size_1.height);

        if (pos_1.x > pos_2.x) // 1 is on the right
        {
            if (d <= size_2.width || d <= size_2.height)
            {
                can_attack = true;
            }
        }
        else // 1 is on the left
        {
            if (d <= size_1.width || d <= size_1.height)
            {
                can_attack = true;
            }
        }

        return false;
    }
}