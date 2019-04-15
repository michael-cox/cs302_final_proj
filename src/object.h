#ifndef OBJECT_HPP
#define OBJECT_HPP
#include <iostream>
#include <SDL2/SDL>
#include <vector>

struct object {
	bool firm;
	int x, y, w, h;
	SDL_Texture * t;

	virtual void render();
};

#endif


