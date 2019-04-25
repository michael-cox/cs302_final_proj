/*
 *
 * File: enemy.cpp
 * Phillip Chu
 * ---------------
 * Implements the enemy class.
 */

#ifndef ENEMY_CPP
#define ENEMY_CPP

#include "enemy.hpp"

#define ENEMY_W 68
#define ENEMY_H 82

std::string e_statusToString(characterStatus status)
{
	switch(status)
	{
		case MOVING_UP:
			return "idle";
		case MOVING_DOWN:
			return "idle";
		case JUMP:
			return "idle";
        case IDLE:
            return "idle";
        case ATTACK:
            return "attack";
        case MOVING_RIGHT:
            return "walk";
        case MOVING_LEFT:
            return "walk";
        default:
            return "idle";
	}
}

enemy::enemy(std::string name, int x, int y, graphicProcessor * graphicProc, soundProcessor * soundProc)
    : character(name, x, y, ENEMY_W, ENEMY_H, 100, 0.7, graphicProc), _soundProc(soundProc)
{
	//39, 21
	characterStatus status;
	std::string path;
	//omitted _g and _gVelocity
	int numTextures = 0;
	
	
	for (int i = 0; i < 7; ++i)
	{
		status = (characterStatus)i;
		path = "assets/zombiefiles/png/male/" + e_statusToString(status);
		switch(status)
		{
			case MOVING_UP:
				numTextures = 10;
	        case MOVING_DOWN:
				numTextures = 10;			 
	        case JUMP:
				numTextures = 10;			 
			case IDLE:
				numTextures = 15; //15
				break;
			case ATTACK:
				numTextures = 8; //8
				break;
			case MOVING_RIGHT:
				numTextures = 10; //10
				break;
			case MOVING_LEFT:
				numTextures = 10; //10
				break;
			default:
				break;
		}
		animation * a = new animation(path, PNG, 4, numTextures, ENEMY_W, ENEMY_H, _graphicProc);
		_animations[status] = a;
	}
}

enemy::~enemy()
{
	for (std:: unordered_map<characterStatus,animation*>::iterator i = _animations.begin(); i != _animations.end(); ++i) 
		delete i->second;
}

void enemy::updateStatus(characterStatus status)
{
	if (_status != ATTACK) { _prevStatus = _status; }
    switch (status) {
        case MOVING_RIGHT:
            _status = status; 
            _currVelocityX = _velocity;
            _facing = RIGHT;
            break;
        case MOVING_LEFT:
            _status = status;
            _currVelocityX = -1 * _velocity;
            _facing = LEFT;
            break;
		case IDLE:
			_status = status;
			_currVelocityX = 0;
            break;
        default:
            break;
	}
}

void enemy::move()
{
	_y += _currVelocityY;
	_x += _currVelocityX;
	//barrier check
	if (_y > _graphicProc->getResolutionH() * 4 / 5 - _h) {
		_y = _graphicProc->getResolutionH() * 4 / 5 - _h;
		_currVelocityY = 0;
		_jumped = 0;
	}
	else {
		_currVelocityY += _velocity;
	}
}

void enemy::render()
{
	_animations[_status]->render(_x, _y, _graphicProc, _facing == RIGHT ? 0 : 1);
}

void enemy::seekPlayer(int playerX)
{

    if(playerX < _x) updateStatus(MOVING_LEFT);
    else updateStatus(MOVING_RIGHT);

}

#endif
