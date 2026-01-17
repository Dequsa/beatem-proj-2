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
#include "infobar.h"

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
	InfoBar infobar({0.0f, 0.0f}, {utility::SCREEN_WIDTH, 26}, screen.game_renderer);
	Camera camera(0.0f, -950.0f, 1.3f, PlayerConstants::WALKING_SPEED);
	Map game_map(screen.game_renderer, utility::MAP_PATH);
	Player player(screen.game_renderer);
	Enemy enemy(1, 800.0f, 900.0f, screen.game_renderer);

	SDL_Event e;
	bool quit = false;

	Uint64 last_time = SDL_GetPerformanceCounter();
	int desired_frame_time = 1000 / utility::MONITOR_REFRESH_RATE; // in milliseconds
	const Uint64 PC_FREQ = SDL_GetPerformanceFrequency();
	while (!quit)
	{

		Uint64 current_time = SDL_GetPerformanceCounter();
		float delta_time = static_cast<float>(current_time - last_time) / PC_FREQ; // precise seconds | how many times CPU has ticks/s

		last_time = current_time;

		// dont let delta time be larger then 10fps
		if (delta_time > 0.1f)
			delta_time = 0.1f;
		// delay frames if the are faster then expected
		if (delta_time * 1000.0f < desired_frame_time)
		{
			SDL_Delay(static_cast<Uint64>(desired_frame_time - delta_time * 1000.0f)); // cap at monitor refresh rate (set in config) kind of V-SYNC
		}

		// debug
		if (utility::DEBUG_MODE)
		{
			printf("Delta time: %f seconds\n", delta_time);
		}

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
		DrawingFunctions::DrawBackground(screen.game_renderer, game_map.get_map_texture(), camera.get_position().x, camera.get_position().y, CameraConstants::BACKGROUND_SIZE_RATIO);

		// draw player sprite
		DrawingFunctions::DrawFrame(screen.game_renderer, player.get_sprite_sheet(), player.get_position().x, player.get_position().y, player.get_scale(), player.get_flip_state(),
									camera.get_position().x, camera.get_position().y,
									player.get_animation().frame_height, player.get_animation().frame_width,
									player.get_animation().current_frame, player.get_current_action(), 0.0f);

		// // draw enemy sprite
		// DrawingFunctions::DrawFrame(screen.game_renderer, enemy.get_sprite_sheet(), enemy.get_position().x, enemy.get_position().y, 0.67f, enemy.GetFlipState(), camera.get_position().x,
		// 							 camera.get_position().y, enemy.get_animation().sheet_height, enemy.get_animation().sheet_width, enemy.get_animation().current_frame, 0, 5.0f);

		// DrawingFunctions::draw_sprite(screen.game_renderer, player.get_sprite_sheet(), player.get_position().x, player.get_position().y, 0.2f, player.get_flip_state(), camera.get_position().x, camera.get_position().y);

		// draw infobar
		infobar.update_infobar(player.get_health(), 0.0f, delta_time, screen.game_renderer);

		SDL_RenderPresent(screen.game_renderer);
	}

	// free-up everything
	close(&screen);
	player.~Player();

	return 0;
}
