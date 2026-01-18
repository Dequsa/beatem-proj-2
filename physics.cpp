#include "physics.h"
#include "camera.h"
#include <cmath>
#include <cstdio>

namespace MovementFunctions
{
    constexpr float MIN_SIZE = 3.5f;
    constexpr float MAX_SIZE = 5.0f;
    constexpr float FLOOR_START_Y = 1197.0f;
    // from bmp
    constexpr float REAL_FLOOR_SIZE = 1047.0f;
    
    // bounding system
    void bound_entity(float &x, float &y, int w, int h, int map_w, int map_h)
    {
        // bound x
        if (x + w > map_w) // right side of the map
            x = map_w - w;

        if (x < 0.0f) // left side
            x = 0.0f;

        // bound y
        if (y < FLOOR_START_Y - h) // floor top
            y = FLOOR_START_Y - h;

        if (y > map_h - h) // bottom of the screen
            y = map_h - h;
    }

    // calculating velocity
    float calculate_velocity(float dt, float base_vel)
    {
        return base_vel * dt * 1000.0f; // scale speed by delta_time
    }

    // moving system
    void move_object_x(float velocity, float &x, direction_t current_direction)
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

    void scale_object(float &y, float &scale)
    {
        float floor_size = REAL_FLOOR_SIZE * CameraConstants::BACKGROUND_SIZE_RATIO;
        float scale_step = (MAX_SIZE - MIN_SIZE) / floor_size;
        float scale_progress = y - FLOOR_START_Y; // progress tracking
        scale = (scale_step * scale_progress) + MIN_SIZE;
    }

    void move_object_y(float velocity, float &y, float &scale, direction_t current_direction)
    {
        switch (current_direction)
        {
        case direction_t::DIRECTION_UP:
            y -= velocity;
            break;
        case direction_t::DIRECTION_DOWN:
            y += velocity;
            break;
        default:
            return;
        }
        // scale change with progress
        
    }

    void move_object(float velocity, float &x, float &y, float &scale, direction_t current_direction, int w, int h, int map_w, int map_h)
    {
        scale_object(y,scale);
        
        if (current_direction == direction_t::DIRECTION_NONE)
        {
            return;
        }

        move_object_x(velocity, x, current_direction);
        move_object_y(velocity, y, scale, current_direction);
        bound_entity(x, y, w, h, map_w, map_h);

        if (utility::DEBUG_MODE)
        {
            printf("X: %f | Y:%f\n", x, y);
        }
    }

    void dash(direction_t last_direction, position_t &pos, dimensions_t size,  int map_width, int map_height, float &scale, float strength)
    {
        scale_object(pos.y, scale);

        switch (last_direction)
        {
            case direction_t::DIRECTION_UP:
            pos.y -= strength;
            break;
            case direction_t::DIRECTION_DOWN:
            pos.y += strength;
            break;
            case direction_t::DIRECTION_LEFT:
            pos.x -= strength;
            break;
            case direction_t::DIRECTION_RIGHT:
            pos.x += strength;
            break; 
}

        bound_entity(pos.x, pos.y, size.width, size.height, map_width, map_height);
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
}