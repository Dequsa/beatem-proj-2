#pragma once
#include "structs.h"

namespace MovementFunctions
{
    constexpr float floor_top = 1163.0f;

    void bound_entity(float &x, float &y, int w, int h, int map_w, int map_h);

    void move_object_x(float velocity, float &x, float &y, direction_t current_direction);

    void move_object_y(float velocity, float &x, float &y, float &scale, direction_t current_direction);

    void move_object(float velocity, float &x, float &y, float &scale, direction_t current_direction, int w, int h, int map_w, int map_h);

    float calculate_velocity(float dt, float base_vel);
}

namespace AttackFunctions
{
    bool check_hitbox(position_t pos_1, dimensions_t size_1, position_t pos_2, dimensions_t size_2);

    // void attack(int &target_helth, float &source_cooldown, attack_t attack_move);
}