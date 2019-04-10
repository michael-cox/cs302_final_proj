#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

struct object {
	bool firm;
	int x, y, w, h;
	SDL_Texture * t;

	virtual void render() = 0;
};

#endif


