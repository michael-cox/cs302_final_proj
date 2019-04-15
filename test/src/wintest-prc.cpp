
// include SDL header file
#include <SDL2/SDL.h>

// initialize global variables, window pointer and renderer pointer
SDL_Window * g_pWindow = 0;
SDL_Renderer * g_pRenderer = 0;

// main
int main(int argc, char * argv[]) {

	// initialize everything in SDL	
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {

		// creates a window with the specified parameters and sets it equal to the
		// window pointer
		g_pWindow = SDL_CreateWindow("Chapter 1: Setting up SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

		// check if the window assignment was not successful
		if (g_pWindow != 0) {
			
			// if so, create renderer
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
		}	
	}
	else {
		// SDL could not initialize
		return 1;
	}
		
		// set window color
		SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);

		// creates the black window
		SDL_RenderClear(g_pRenderer);

		// presents the window to the screen
		SDL_RenderPresent(g_pRenderer);

		// holds the window open for 5 seconds
		SDL_Delay(5000);

		// quits the program
		SDL_Quit();

		return 0;
}
