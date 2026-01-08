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

	// create window
	screen_create(&screen);

	// initialization of classes
	Camera camera(0.0f, -950.0f, 1.3f, PlayerConstants::WALKING_SPEED);
	Map game_map(screen.game_renderer, utility::MAP_PATH);
	Player player(screen.game_renderer);
	Enemy enemy(1, 800.0f, 900.0f, screen.game_renderer);

	SDL_Event e;
	bool quit = false;

	int last_time = SDL_GetPerformanceCounter();
	while (!quit)
	{
		int desired_frame_time = 1000 / utility::MONITOR_REFRESH_RATE; // in milliseconds
		int current_time = SDL_GetPerformanceCounter();
		float delta_time = (float)(current_time - last_time) / SDL_GetPerformanceFrequency();

		last_time = current_time;

		// delay frames if the are faster then expected
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

		// SDL event handler
		while (SDL_PollEvent(&e))
		{
			handle_event(&e, &quit, player);
		}

		// player movement
		player.move(e, delta_time, camera.get_state(), game_map.get_width(), game_map.get_height());

		// camera movement
		camera.update(player.get_position(), game_map.get_width(), game_map.get_height());

		// entity movement
		enemy.update(player, delta_time);
		
		// draw background
		DrawingFunctions::draw_background(screen.game_renderer, game_map.get_map_texture(), camera.get_position().x, camera.get_position().y, CameraConstants::BACKGROUND_SIZE_RATIO);

		// draw player sprite
		DrawingFunctions::draw_frame(screen.game_renderer, player.get_sprite_sheet(), player.get_position().x, player.get_position().y, player.get_scale(), player.get_flip_state(), camera.get_position().x,
									 camera.get_position().y, player.get_animation().sheet_height, player.get_animation().sheet_width, player.get_animation().current_frame, 5.0f);

		// draw enemy sprite
		DrawingFunctions::draw_frame(screen.game_renderer, enemy.get_sprite_sheet(), enemy.get_position().x, enemy.get_position().y, PlayerConstants::SPRITE_SCALE, player.get_flip_state(), camera.get_position().x,
									 camera.get_position().y, enemy.get_animation().sheet_height, enemy.get_animation().sheet_width, enemy.get_animation().current_frame, 5.0f);

		//DrawingFunctions::draw_sprite(screen.game_renderer, player.get_sprite_sheet(), player.get_position().x, player.get_position().y, 0.2f, player.get_flip_state(), camera.get_position().x, camera.get_position().y);

		SDL_RenderPresent(screen.game_renderer);
	}

	// free-up everything
	close(&screen);
	player.~Player();

	return 0;
}
