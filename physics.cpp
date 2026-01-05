#include "physics.h"
namespace PhysicsFunctions
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

}