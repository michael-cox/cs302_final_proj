/*
 * File: player.cpp
 * Michael Cox
 * ----------------
 * Implements the player
 * class.
 */

#include "player.hpp"

player::player(std::string name, int x, int y, imageProcessor * imgProc) : character(name, x, y, 39, 21, 100, 2.2, imgProc) 
{
    _g = 3;
    _gVelocity = 0;
    _texture = _imgProc->makeTexture("assets/ninjaadventurenew/png/Idle__001.png", png);
}

void player::updateStatus(characterStatus status)
{
    _status = status;
}

void player::move()
{
    switch(_status)
    {
        case MOVING_UP:
            _y -= _velocity;
            break;
        case MOVING_DOWN:
            if(_y < 900)
                _y += _velocity;
            break;
        case MOVING_RIGHT:
            _x += _velocity;
            break;
        case MOVING_LEFT:
            _x -= _velocity;
            break;
        default:
            break;
    }
    if(_y < 760)
    {
        _y += _gVelocity;
        _gVelocity += _g;
    }
}

/* TODO: Put actual thought into how to do this */
void player::render()
{
    int textureW, textureH;
    SDL_QueryTexture(_texture, NULL, NULL, &textureW, &textureH);
    _imgProc->renderTextureWithScaling(_texture, _x, _y, textureW, textureH, _w, _h);
}
