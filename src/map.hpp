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
    map(int w, int h) : gameMap(h, std::pair<bool,std::vector<object*>>(false,std::vector<object*>(w, nullptr))) { }
    std::vector< std::pair<bool,std::vector<object*>>> gameMap;
};

#endif
