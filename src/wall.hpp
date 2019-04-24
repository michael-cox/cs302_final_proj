/*
 * File: wall.hpp
 * Phillip Chu and Michael Cox
 * ---------------
#ifndef WALL_HPP
#define WALL_HPP

#include <SDL2/SDL.h>
#include "object.hpp"
#include <string>

struct wall : public object {
	wall(int x, int y, int w, int h, graphicProcessor * graphicProc, std::string fileName, imageType imgType) : object(x, y, w, h, true, graphicProc) {
		texture = _graphicProc->makeTexture(fileName, imgType);
	}
	SDL_Texture * texture;
}

#endif

