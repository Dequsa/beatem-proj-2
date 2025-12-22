#include <SDL.h>

typedef struct {
    SDL_Window* game_window;
    SDL_Surface* game_surface;
    SDL_Surface** sprites;
}screen_t;

bool screen_init_SDL();

// bool screen_create_window(screen_t* screen);

// bool load_all_sprites_to_memory(screen_t* screen);

void close(screen_t* screen);

void screen_create(screen_t* screen);