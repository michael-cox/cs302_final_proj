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

/* Enum for different statuses */
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

/* Enum for direction the character is facing */
enum direction
{
	LEFT,
	RIGHT
};

/* Abstract class for characters */
class character : protected object
{
    protected:
        std::string _name;
		double _health;
        double _velocity;
		double _currVelocityX;
		double _currVelocityY;
		direction _facing;
		bool _jumped;
		bool _attacked;
        characterStatus _status;
		characterStatus _prevStatus;
        std::unordered_map<characterStatus,animation*> _animations;

    public:
        character(std::string name, int x, int y, int w, int h, double health,
                double velocity, graphicProcessor * graphicProc)
            : object(x, y, w, h, true, graphicProc), _name(name), _health(health), _velocity(velocity),
            _facing(RIGHT)

        { _currVelocityX = 0; _currVelocityY = 0; }
        virtual void updateStatus(characterStatus status) = 0;
        virtual void move() = 0;
        virtual void render() = 0;

};

#endif
