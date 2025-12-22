typedef enum {
	ENTITY_STATIC_OBJECT,
	ENTITY_OBJECT,
	ENTITY_ENEMY,
	ENTITY_PLAYER,
}entity_type;

typedef struct{
	float x;
	float y;
	float z;
}position_t;

typedef struct {
	int width;
	int height;
}dimensions_t;

typedef struct {
	position_t* origin; // this will be a pointer to position so there is no need to constantly copy value
	dimensions_t dimentions;
}hitbox_t;

typedef struct {
	int dmg;
	int frames;
	int animation;
}attack_t;

typedef struct {
	int id;
	int sprite_id;
	entity_type type;
	position_t position;
	
	union {
		struct {
			bool is_alive;
			int current_health;
			hitbox_t hitbox;
			attack_t current_attack;
		} enemy;

		struct {
			bool is_destroyed;
			dimensions_t size;
		} object;

		struct {
			bool is_alive;
			int current_health;
			hitbox_t hitbox;
			attack_t current_attack;
		} player;

		struct {
			dimensions_t size;
		} static_object;
	} data;
}entity_t;