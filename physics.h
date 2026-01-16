#pragma once
#include "structs.h"

namespace MovementFunctions
{
    void bound_entity(position_t &pos, SDL_FRect &collision_box, int map_w, int map_h);

    void move_object_x(float velocity, float &x, direction_t current_direction);

    void move_object_y(float velocity, float &y, float &scale, direction_t current_direction);

    void move_object(float velocity, float &x, float &y, float &scale, direction_t current_direction, int w, int h, float offset_left, float offset_right, int map_w, int map_h);

    float calculate_velocity(float dt, float base_vel);
}

namespace AttackFunctions
{
    bool check_hitbox(position_t pos_1, dimensions_t size_1, position_t pos_2, dimensions_t size_2);
}