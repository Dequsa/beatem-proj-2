#pragma once

enum class enitity_type
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
    float width;
    float height;
} dimensions_t;

typedef struct
{
    float off_set_x;
    float off_set_y;
    dimensions_t size;
} hitbox_t;

typedef struct
{
    int id;
    int dmg;
    int current_frames;
    int animation;
} attack_t;

typedef struct
{
    SDL_Texture* sprite_sheet;
    int frame_width;
    int frame_height;
    int total_frames;
    int current_frame;
    float frame_duration; // in msec
    float timer;
} animation_t;

typedef struct
{
    int id;
    int sprite_id;
    enitity_type type;
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