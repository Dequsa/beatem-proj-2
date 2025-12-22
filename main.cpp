#include<math.h>
#include<stdio.h>
#include<string.h>
#include <SDL.h>
#include "entities.h"
#include "config_loader.h"
#include "map_handler.h"
#include "physics.h"
#include "screen.h"
#include "player.h"

int main(int argc, char* argv[]) {	
	screen_t screen{};
	
	screen_create(&screen);
	
	close(&screen);

	//printf("it worked");
	return 0;
}
