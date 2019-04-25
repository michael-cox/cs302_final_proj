/*
 * File: wall.hpp
 * Phillip Chu
 * ---------------
 * Provides an interface for
 * the wall object.
 */

#ifndef WALL_HPP
#define WALL_HPP

#include <SDL2/SDL.h>
#include <string>
#include "object.hpp"

/* wallType - enum for wall types (corner, edge, etc) */
enum wallType
{
    LEFT_EDGE_SNOW,
    CENTER_SNOW,
    RIGHT_EDGE_SNOW,
    CENTER_DIRT
};

struct wall : public object
{

    wallType type;
    sprite * texture;

    /* Constructor - fileName is an image */
    wall(int x, int y, int w, int h, graphicProcessor * graphicProc,
            std::string fileName, imageType imgType) 
        : object(x, y, w, h, true, graphicProc)
    {
        texture = new sprite(fileName, imgType, w, h, _graphicProc);
    }

    /* render - draws the wall on the screen */
    void render()
    {
        texture->render(_x, _y, _graphicProc);
    }
};

#endif

