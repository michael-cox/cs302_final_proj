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
#include <unordered_map>
#include "object.hpp"

enum characterStatus
{
    MOVING_UP,
    MOVING_DOWN,
    MOVING_RIGHT,
    MOVING_LEFT,
	JUMP,
    IDLE,
    ATTACK
};

class character : protected object
{
    protected:
        std::string _name;
        double _health;
        double _velocity;
		double _currVelocityX;
		double _currVelocityY;
		bool _jumped;
        characterStatus _status;
        std::unordered_map<characterStatus,animation*> _animations;
    public:
        character(std::string name, int x, int y, int w, int h, double health,
                double velocity, graphicProcessor * graphicProc)
            : object(x, y, w, h, true, graphicProc), _name(name), _health(health), _velocity(velocity)
        { _currVelocityX = 0; _currVelocityY = 0; }
        ~character()
        {
            for(std::unordered_map<characterStatus,animation*>::iterator i = _animations.begin(); i != _animations.end(); ++i)
                delete i->second;
        }
        virtual void updateStatus(characterStatus status) = 0;
        virtual void move() = 0;
        virtual void render() = 0;
};

#endif
