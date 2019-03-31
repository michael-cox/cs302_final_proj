/* Robert Smith
 * 3/26/19
 * keyTest.cpp
 * Testing keyboard inputs by having keys correlate to a screen movement.
 * Start with small amount of keys, then increase.
 * Things to consider: single press, holding, combination inputs
 */
#include <SDL2/SDL.h>

int main(int argc, char **argv) {
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window *win = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, 0);

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);

	//base black window
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
	SDL_RenderClear(ren);

	//Currently implemented: ESC key closes the window and program on press
	//W for red, A, for green, S for blue, D for white, Space for black
	SDL_Event event;
	while (true) {
		SDL_RenderPresent(ren);
		//handle key cases
		//check to see if event is happening
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						SDL_Quit();
						return 0;
					case SDLK_w:
						SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
						SDL_RenderClear(ren);
						break;
					case SDLK_a:
						SDL_SetRenderDrawColor(ren, 0, 255, 0, 0);
						SDL_RenderClear(ren);
						break;
					case SDLK_s:
						SDL_SetRenderDrawColor(ren, 0, 0, 255, 0);
						SDL_RenderClear(ren);
						break;
					case SDLK_d:
						SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
						SDL_RenderClear(ren);
						break;
					case SDLK_SPACE:
						SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
						SDL_RenderClear(ren);
						break;
				}
			}
		}
	}
}
