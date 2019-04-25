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

player::player(std::string name, int x, int y, graphicProcessor * graphicProc, soundProcessor * soundProc) : character(name, x, y, 78, 42, 100, 2.2, graphicProc), _soundProc(soundProc) 
{
    characterStatus status;
    std::string path;
    for(int i = 0; i < 7; ++i)
    {
        status = (characterStatus)i;
        path = "assets/ninja/png/" + statusToString(status);
        animation * a = new animation(path, PNG, 4, 10, 78, 42, _graphicProc);
        _animations[status] = a;
    }
}

player::~player()
{
    for(std::unordered_map<characterStatus,animation*>::iterator i = _animations.begin(); i != _animations.end(); ++i)
        delete i->second;
}

void player::updateStatus(characterStatus status)
{
    switch (status) {
        case JUMP:
            if (!_jumped) {
                _soundProc->playSound("playerJump.wav");
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
            _soundProc->playSound("playerShoot.wav");
            break;
        default:
            break;
    }
}

void player::move()
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

/* TODO: Put actual thought into how to do this */
void player::render()
{
    _animations[_status]->render(_x, _y, _graphicProc);
}
