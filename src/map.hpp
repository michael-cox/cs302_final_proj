/*
 * Michael Cox
 * CS302 March 14, 2019
 * File: map.hpp
 * -----------------------
 * Provides an interface for the map object.
 */

#include <cstdlib>

struct Map
{
    size_t _width;
    size_t _height;
    char * _map;
    Map(size_t width, size_t height) : _width(width), _height(height)
    {
        _map = (char*)(std::calloc(width * height, sizeof(char)));
    }
    ~Map()
    {
        delete [] _map;
    }
};
