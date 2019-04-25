/*
 * File: player.cpp
 * Michael Cox
 * ----------------
 * Implements the player
 * class.
 */

#include "player.hpp"

std::string statusToString(characterStatus status)
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

player::player(std::string name, int x, int y, graphicProcessor * graphicProc, soundProcessor * soundProc) : character(name, x, y, 39, 21, 100, 2.2, graphicProc), _soundProc(soundProc), _facing(RIGHT) 
{
    _g = 3;
    _gVelocity = 0;
    characterStatus status;
    std::string path;
    for(int i = 0; i < 7; ++i)
    {
        status = (characterStatus)i;
        path = "assets/ninja/png/" + statusToString(status);
        animation * a = new animation(path, PNG, 4, 10, 39, 21, _graphicProc);
        _animations[status] = a;
    }
}

player::~player()
{
    for(std::unordered_map<characterStatus,animation*>::iterator i = _animations.begin(); i != _animations.end(); ++i)
        delete i->second;
	for (size_t i = 0; i < projList.size(); i++) { delete projList[i]; }
}

void player::updateStatus(characterStatus status)
{	
	if (_status != ATTACK) { _prevStatus = _status; }
    switch (status) {
        case JUMP:
            if (!_jumped) {
                _soundProc->playSound("playerJump.wav");
                _currVelocityY = -25;
                _jumped = 1;
            }	
            break;
        case MOVING_RIGHT:
			if (_status == MOVING_LEFT || _prevStatus == MOVING_LEFT) { 
				_status = IDLE; 
				_currVelocityX = 0;
			}
			else {
				_facing = RIGHT;
				_status = status; 
				_currVelocityX = _velocity;
			}
            break;
        case MOVING_LEFT:
			if (_status == MOVING_RIGHT || _prevStatus == MOVING_RIGHT) { 
				_status = IDLE; 
				_currVelocityX = 0;
			}
			else {
				_facing = LEFT;
				_status = status;
				_currVelocityX = -1 * _velocity;
			}
            break;
        case ATTACK:
			_status = status;
			projList.push_back(new projectile(_x + (_w / 2), _y + (_h / 2), _graphicProc, _facing));
			_soundProc->playSound("playerShoot.wav");
            break;
		case IDLE:
			_status = status;
			_currVelocityX = 0;
        default:
            break;
    }
}

void player::move()
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

/* TODO: Put actual thought into how to do this */
void player::render()
{ 
	if (_animations[_status]->render(_x, _y, _graphicProc) && _status == ATTACK) {
		updateStatus(_prevStatus);
	}
	for (size_t i = 0; i < projList.size(); i++) {
		projList[i]->render();
	}
}

void projectile::move() {
	_x += _currVelocityX;
	//if hits wall, disappear
}

void projectile::render() {
	_sprite->render(_x, _y, _graphicProc);
}
