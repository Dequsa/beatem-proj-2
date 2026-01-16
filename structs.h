#pragma once
#include "utility.h"

enum class type_t
{
    ENTITY_PLAYER = 0,
    ENTITY_ENEMY, // 1 etc...
    ENTITY_STATIC_OBJECT,
    ENTITY_OBJECT,
};

enum class direction_t
{
    DIRECTION_NONE = 0,
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT
};

typedef struct
{
    float x;
    float y;
    float z; // idk if i will need z coordinate but just in case
} position_t;

typedef struct
{
    int width;
    int height;
} dimensions_t;

typedef struct
{
    float off_set_x;
    float off_set_y;
    dimensions_t size;
} hitbox_t;

typedef struct
{
    const char *name;
    int dmg;
    float cooldown;
} attack_t;

typedef struct
{
    SDL_Texture *sprite_sheet;
    int frame_width;  // it should be frame instead of sheet
    int frame_height; // it should be frame instead of sheet
    int *total_frames;
    int current_frame;
    ActionSheet current_action;
    float frame_duration; // in msec
    float timer;
} animation_t;

typedef struct
{
    int id;
    int sprite_id;
    type_t type;
    position_t position;

    union
    {
        struct
        {
            bool is_alive;
            int current_health;
            hitbox_t hitbox;
            attack_t current_attack;
        } enemy;

        struct
        {
            bool is_destroyed;
            dimensions_t size;
        } object;

        struct
        {
            dimensions_t size;
        } static_object;
    } data;
} entity_t;

namespace Attacks
{
    constexpr int ATTACKS_COUNT = 1;

    enum class Number
    {
        LIGHT = 0,
        HEAVY,

        Count // gives count of all items
    };

    // name | damage | cooldown [sec]
    constexpr attack_t LIGHT{"Light Attack", 5, 8};
    constexpr attack_t HEAVY{"Heavy Attack", 15, 30};
};

enum class ActionSheet
{
    spell_cast_up = 0,
    spell_cast_left,
    spell_cast_down,
    spell_cast_right,

    thrust_up,
    thrust_left,
    thrust_down,
    thrust_right,

    walk_up,
    walk_left,
    walk_down,
    walk_right,

    slash_up,
    slash_left,
    slash_down,
    slash_right,

    shoot_up,
    shoot_left,
    shoot_down,
    shoot_right,

    hurt_up,
    hurt_left,
    hurt_down,
    hurt_right,

    climb_up,
    climb_left,
    climb_down,
    climb_right,

    idle_up,
    idle_left,
    idle_down,
    idle_right,

    jump_up,
    jump_left,
    jump_down,
    jump_right,

    sit_up,
    sit_left,
    sit_down,
    sit_right,

    emote_up,
    emote_left,
    emote_down,
    emote_right,

    run_up,
    run_left,
    run_down,
    run_right,

    watering_up,
    watering_left,
    watering_down,
    watering_right,

    combat_idle_up,
    combat_idle_left,
    combat_idle_down,
    combat_idle_right,

    one_handed_slash_up,
    one_handed_slash_left,
    one_handed_slash_down,
    one_handed_slash_right,

    one_handed_backslash_up,
    one_handed_backslash_left,
    one_handed_backslash_down,
    one_handed_backslash_right,

    one_handed_halfslash_up,
    one_handed_halfslash_left,
    one_handed_halfslash_down,
    one_handed_halfslash_right,

    slash_oversize_up,
    slash_oversize_left,
    slash_oversize_down,
    slash_oversize_right
};