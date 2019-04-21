/*
 * File: player.cpp
 * Michael Cox
 * ----------------
 * Implements the player
 * class.
 */

#include "player.hpp"

player::player(std::string name, int x, int y, imageProcessor * imgProc) : character(name, x, y, 85, 45, 100, 2.2, imgProc) 
{
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
}

/* TODO: Put actual thought into how to do this */
void player::render()
{
    int textureW, textureH;
    SDL_QueryTexture(_texture, NULL, NULL, &textureW, &textureH);
    _imgProc->renderTextureWithScaling(_texture, _x, _y, textureW, textureH, _w, _h);
}
