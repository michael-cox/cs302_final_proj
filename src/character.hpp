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

enum characterStatus
{
    MOVING_UP,
    MOVING_DOWN,
    MOVING_RIGHT,
    MOVING_LEFT,
    STILL,
    ATTACK
};

class character : protected object
{
    protected:
        std::string _name;
        double _health;
        double _velocity;
        characterStatus _status;
        std::map<characterStatus,animation> _animations;
    public:
        character(std::string name, int x, int y, int w, int h, double health,
                double velocity, imageProcessor * imgProc)
            : object(x, y, w, h, true, imgProc), _name(name), _health(health), _velocity(velocity)
        {}
        virtual void updateStatus(characterStatus status) = 0;
        virtual void move() = 0;
        virtual void render() = 0;
};

#endif
