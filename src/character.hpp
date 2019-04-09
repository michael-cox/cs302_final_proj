/*
 * Michael Cox
 * CS307 Final Project
 * File: character.hpp
 * -------------------
 * Provides an interface for
 * the character object.
 */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include "object.hpp"

enum direction
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

class character : protected object
{
    protected:
        double _health;
        double _speed;
    public:
        character(std::string name, double x, double y);
        virtual void move(direction dir);
        virtual void render() = 0;
};

#endif
