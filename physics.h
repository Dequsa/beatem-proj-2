#pragma once
#include "structs.h"

namespace MovementFunctions
{
    void check_bounds(float max_x, float max_y, float min_x, float min_y);

    void move_object_x(float velocity, float *x, float *y, direction_t current_direction);

    void move_object_y(float velocity, float *x, float *y, direction_t current_direction);

    void move_object(float speed, float *x, float *y, direction_t current_direction);

    float calculate_velocity(float dt, float base_vel);

    bool check_hitbox(position_t pos_1, dimensions_t size_1, position_t pos_2, dimensions_t size_2);
}
