// #define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

// extern "C" {
// #include"./SDL2-2.0.10/include/SDL.h"
// #include"./SDL2-2.0.10/include/SDL_main.h"
// }


#define SDL_MAIN_HANDLED
#include <SDL.h>

int check_SDL() {
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("error during initialization of SDL err: %s \n", SDL_GetError());
		return 1;
	}

	return 0;
}


int main(int argc, char* argv[]) {
	if (check_SDL()) return 1;

	SDL_SetMainReady();
	SDL_Init(SDL_INIT_VIDEO);
	printf("it worked");
	return 0;
}
