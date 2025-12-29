#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include "entities.h"
#include "config_loader.h"
#include "map_handler.h"
#include "screen.h"
#include "player.h"
#include "utility.h"
#include "camera.h"

void handle_event(SDL_Event *e, bool *quit, Player &player)
{
	switch (e->type)
	{
	case SDL_QUIT:
		*quit = true;
		break;
	case SDL_KEYDOWN:
		if (e->key.keysym.sym == SDLK_ESCAPE)
			*quit = true;

		break;
	}
}

int main(int argc, char *argv[])
{
	screen_t screen{};

	screen_create(&screen);

	// set backgroun's origin at 0 0
	Camera camera(0.0f, 0.0f, 0.90f);
	Map game_map(screen.game_renderer, utility::MAP_PATH);
	Player player(screen.game_renderer);
	
	SDL_Event e;
	bool quit = false;

	int last_time = SDL_GetPerformanceCounter();

	while (!quit)
	{
		int desired_frame_time = 1000 / utility::MONITOR_REFRESH_RATE; // in milliseconds
		int current_time = SDL_GetPerformanceCounter();
		float delta_time = (float)(current_time - last_time) / SDL_GetPerformanceFrequency();
		last_time = current_time;
		if (delta_time * 1000 < desired_frame_time)
		{
			SDL_Delay((Uint32)(desired_frame_time - delta_time * 1000)); // cap at monitor refresh rate (set in config) kind of V-SYNC
		}

		// debug
		if (utility::DEBUG_MODE)
		{
			printf("Delta time: %f seconds\n", delta_time);
		}

		// SDL_SetRenderDrawColor(screen.game_renderer, 0, 0, 0, 255);
		SDL_RenderClear(screen.game_renderer);

		while (SDL_PollEvent(&e))
		{
			handle_event(&e, &quit, player);
		}

		player.move(e, delta_time);
		camera.move(player.get_direction(), player.get_speed());

		if (utility::DEBUG_MODE)
		{
			printf("Camera Position X: %f, Y: %f\n", camera.get_x, camera.get_y);
			printf("Player Position X: %f, Y: %f\n", player.get_position().x, player.get_position().y);
		}

		// draw background
		draw_sprite(screen.game_renderer, game_map.get_map_texture(), camera.get_x(), camera.get_y(), camera.get_zoom(), SDL_FLIP_NONE);

		// draw player sprite
		draw_sprite(screen.game_renderer, player.get_sprite_sheet(), player.get_position().x, player.get_position().y, 0.2f, player.get_flip_state());
		
		SDL_RenderPresent(screen.game_renderer);
	}

	close(&screen);
	player.~Player();

	return 0;
}
