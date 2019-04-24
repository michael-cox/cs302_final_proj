/*
 * File: player.cpp
 * Michael Cox
 * ----------------
 * Implements the player
 * class.
 */

#include "player.hpp"
#include "sound.hpp"

player::player(std::string name, int x, int y, graphicProcessor * graphicProc, soundProcessor * soundProc) : character(name, x, y, 39, 21, 100, 2.2, graphicProc), _soundProc(soundProc) 
{
    _g = 3;
    _gVelocity = 0;
    _texture = _graphicProc->makeTexture("assets/ninjaadventurenew/png/Idle__001.png", PNG);
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
    int textureW, textureH;
    SDL_QueryTexture(_texture, NULL, NULL, &textureW, &textureH);
    _graphicProc->renderTextureWithScaling(_texture, _x, _y, textureW, textureH, _w, _h);
}
