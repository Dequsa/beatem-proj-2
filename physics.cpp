#include "physics.h"
#include "camera.h"
#include <cmath>
#include <cstdio>

const float floor_top = 1101.0f; // map_height * scale - 460.0f * scale
const float floor_bottom = utility::SCREEN_HEIGHT;

namespace MovementFunctions
{
    // bounding system

    void bound_entity(position_t &pos, SDL_FRect &collision_box, int map_w, int map_h)
    {
        // --- X AXIS (Walls) ---
        if (collision_box.x < 0)
        {
            pos.x -= collision_box.x;
            collision_box.x = 0;
        }
        if (collision_box.x + collision_box.w > map_w)
        {
            float overlap = (collision_box.x + collision_box.w) - map_w;
            pos.x -= overlap;
            collision_box.x -= overlap;
        }

        // --- Y AXIS (The Playable Floor Zone) ---
        // If player walks too far UP (into the background)
        if (collision_box.y < floor_top)
        {
            float overlap = floor_top - collision_box.y;
            pos.y += overlap;
            collision_box.y = floor_top;
        }

        // If player walks too far DOWN (into the foreground/out of screen)
        if (collision_box.y + collision_box.h > floor_bottom)
        {
            float overlap = (collision_box.y + collision_box.h) - floor_bottom;
            pos.y -= overlap;
            collision_box.y -= overlap;
        }
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

    void move_object_y(float velocity, float &y, float &scale, direction_t current_direction)
    {
        float min_size = 2.8f;
        float max_size = 3.0f;
        float distance = 160.0f * CameraConstants::BACKGROUND_SIZE_RATIO;
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

    void move_object(float velocity, float &x, float &y, float &scale, direction_t current_direction, int w, int h, float offset_left, float offset_right, int map_w, int map_h)
    {
        if (current_direction == direction_t::DIRECTION_NONE)
        {
            return;
        }

        move_object_x(velocity, x, current_direction);
        move_object_y(velocity, y, scale, current_direction);
        // bound_entity(x, y, w, h, map_w, map_h, offset_left, offset_right);
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

    // void attack(int &target_helth, float &source_cooldown, attack_t attack_move)
    // {
    //     target_helth -= attack_move.dmg;
    //     source_cooldown = attack_move.cooldown;

    //     printf("Attack: %s\n", attack_move.name);
    // }
}