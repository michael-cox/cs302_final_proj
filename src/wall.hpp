/*
 * File: wall.hpp
 * Phillip Chu
 * ---------------
 */

#ifndef WALL_HPP
#define WALL_HPP

#include <SDL2/SDL.h>
#include "object.hpp"
#include <string>

enum wallType
{
    LEFT_EDGE,
    CENTER,
    RIGHT_EDGE
};

struct wall : public object
{
    wall(int x, int y, int w, int h, graphicProcessor * graphicProc, std::string fileName, imageType imgType) 
        : object(x, y, w, h, true, graphicProc)
    {
        texture = _graphicProc->makeTexture(fileName, imgType);
    }
    wallType type;
    SDL_Texture * texture;
    void render()
    {
        _graphicProc->renderTexture(texture, _x, _y, _w, _h);
    }
};

#endif

