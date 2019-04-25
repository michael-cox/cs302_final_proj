/*
 * File: object.hpp
 * Phillip Chu and Michael Cox
 * ----------------
 * Provides an interface
 * for the object struct,
 * the top of our inheritance
 * hierarchy.
 */

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SDL2/SDL.h>
#include "graphics.hpp"

struct object {

    /* Constructor */
    object(int x, int y, int w, int h, bool firm, graphicProcessor * graphicProc)
        : _x(x), _y(y), _w(w), _h(h), _firm(firm), _graphicProc(graphicProc) {}

    graphicProcessor * _graphicProc;
	int _x, _y, _w, _h;
    bool _firm;

    /* render - generic render function that can be called on any derived class to place it on the
     * screen */
	virtual void render() = 0;
};

#endif
