#include <math.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include "entities.h"
#include "config_loader.h"
#include "map_handler.h"
#include "physics.h"
#include "screen.h"
#include "player.h"
#include "utility.h"

// void button_handler(SDL_Keycode *keycode, bool &quit)
// {
// 	switch (*keycode)
// 	{
// 	case SDLK_w:
// 		printf("W key pressed\n");
// 		break;
// 	case SDLK_a:
// 		printf("A key pressed\n");
// 		break;
// 	case SDLK_s:
// 		printf("S key pressed\n");
// 		break;
// 	case SDLK_d:
// 		printf("D key pressed\n");
// 		break;
// 	case SDLK_l:
// 		printf("L key pressed\n");
// 		break;
// 	case SDLK_h:
// 		printf("H key pressed\n");
// 		break;
// 	case SDLK_ESCAPE:
// 		quit = true;
// 		break;
// 	default:
// 		break;
// 	}
// }

int main(int argc, char *argv[])
{
	screen_t screen{};
	Player player{};

	screen_create(&screen);

	SDL_Event e;
	bool quit = false;

	while (quit == false)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				//button_handler(&e.key.keysym.sym, quit);
				if (player.move(e))
					quit = true;
				break;
			}
		}

		draw_sprite(screen.game_surface, player.get_sprite_surface(), player.get_position().x, player.get_position().y, 1.05f);

		SDL_UpdateWindowSurface(screen.game_window);
	}

	close(&screen);
	player.~Player();

	return 0;
}
