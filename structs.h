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
    int sheet_width;  // it should be frame instead of sheet
    int sheet_height; // it should be frame instead of sheet
    int total_frames;
    int current_frame;
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
    walking_up = 8,
    walking_left,
    walking_down,
    walking_right,
};