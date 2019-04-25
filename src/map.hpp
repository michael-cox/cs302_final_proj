/*
 * Michael Cox
 * CS302 March 14, 2019
 * File: map.hpp
 * -----------------------
 * Provides an interface for the map object.
 */

#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <utility>
#include "object.hpp"

struct map
{

    /* Constructor */
    map(int w, int h)
        : gameMap(h, std::vector<std::pair<bool,std::vector<object*>>>(w,
                    std::pair<bool,std::vector<object*>>(false, std::vector<object*>()))) {}

    /* A map containing a vector of vectors (2D vector for each pixel) - each pixel has a pair of
     * bool of whether or not that pixel is firm (collision) and a vector of objects that are at
     * that position */
    std::vector<std::vector<std::pair<bool,std::vector<object*>>>> gameMap;

};

#endif
