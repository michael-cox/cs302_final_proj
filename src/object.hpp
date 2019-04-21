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
#include "image.hpp"

struct object {
    object(int x, int y, int w, int h, bool firm, imageProcessor * imgProc)
        : _x(x), _y(y), _w(w), _h(h), _firm(firm), _imgProc(imgProc) {}
    imageProcessor * _imgProc;
	int _x, _y, _w, _h;
    bool _firm;
	virtual void render() = 0;
};

#endif
