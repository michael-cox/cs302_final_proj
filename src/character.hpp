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
#include <map>
#include "game_object.hpp"
#include "object.hpp"

enum status
{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    STILL,
    ATTACK
};

class character : protected object
{
    protected:
        double _health;
        double _velocity;
        status _curStatus;
        std::map<status,animation> _animations;
    public:
        character(std::string name, double x, double y);
        virtual void move(status dir);
        virtual void render();
};

#endif
