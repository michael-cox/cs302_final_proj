/*
 * File: enemy.cpp
 * Phillip Chu
 * ---------------
 * Implements the enemy class.
 */

#ifndef ENEMY_CPP
#define ENEMY_CPP

#include "enemy.hpp"

std::string _statusToString(characterStatus status)
{
	switch(status)
	{
		case JUMP:
            return "jump";
        case IDLE:
            return "idle";
        case ATTACK:
            return "throw";
        case MOVING_RIGHT:
            return "run";
        case MOVING_LEFT:
            return "run";
        case MOVING_DOWN:
            return "glide";
        default:
            return "idle";
	}
}

enemy::enemy(std::string name, int x, int y, graphicProcessor * graphicProc, soundProcessor * soundProc) : character(name, x, y, 39, 21, 100, 1.5, graphicProc), _soundProc(soundProc)
{
	characterStatus status;
	std::string path;
	//omitted _g and _gVelocity
	for (int i = 0; i < 7; ++i)
	{
		status = (characterStatus)i;
		path = "assets/zombiefiles/png/" + _statusToString(status);
		animation * a = new animation(path, PNG, 4, 10, 39, 21, _graphicProc);
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
    switch (status) {
        case JUMP:
            if (!_jumped) {
                //_soundProc->playSound("playerJump.wav");
                _currVelocityY -= 25;
                _jumped = 1;
            }
            break;
        case MOVING_DOWN:
            _currVelocityY += _velocity;
            break;
        case MOVING_RIGHT:
            _currVelocityX += _velocity;
            break;
        case MOVING_LEFT:
            _currVelocityX -= _velocity;
            break;
        case ATTACK:
            _soundProc->playSound("enemyAttack.wav");
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
    if (_y > _graphicProc->getResolutionH() * 2 / 3 - _h) {
        _y = _graphicProc->getResolutionH() * 2 / 3 - _h;
        _currVelocityY = 0;
        _jumped = 0;
    }
    else {
        _currVelocityY += _velocity;
    }
}

void enemy::render()
{
    _animations[_status]->render(_x, _y, _graphicProc);
    if(_statusToString(_status) != "idle") SDL_Log("%s", _statusToString(_status).c_str());
}

void enemy::seekPlayer() {
}

#endif

