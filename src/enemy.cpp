/*
 *
 * File: enemy.cpp
 * Phillip Chu
 * ---------------
 * Implements the enemy class.
 */

#include "enemy.hpp"

#define ENEMY_W 68
#define ENEMY_H 82
#define ENEMY_SPEED 1.1

/* Instantiate the cache map */
std::unordered_map<characterStatus,animation*> enemy::_animationCache;

/* Another function to convert the status enum into strings for image loading */
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

/* Constructor */
enemy::enemy(std::string name, int x, int y, graphicProcessor * graphicProc, soundProcessor * soundProc)
    : character(name, x, y, ENEMY_W, ENEMY_H, 100, ENEMY_SPEED, graphicProc), _soundProc(soundProc)
{
	_health = 3;
	characterStatus status;
    animation * a;
	std::string path;
	int numTextures = 0;
	
    /* Take animations from cache to own animation map */
	for (int i = 0; i < 7; ++i)
	{
        status = (characterStatus)i;
        std::unordered_map<characterStatus,animation*>::iterator anim = _animationCache.find(status);
        if(anim != _animationCache.end()) _animations[status] = anim->second; 
    }
}

/* Loads all of the enemy animations into cache */
void enemy::makeCache(graphicProcessor * graphicProc)
{
    animation * a;
    characterStatus status;
    std::string path;
    size_t numTextures;
    for(size_t i = 0; i < 7; ++i)
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
        a = new animation(path, PNG, 4, numTextures, ENEMY_W, ENEMY_H, graphicProc);
        _animationCache[status] = a;
    }
}

/* Clears the cache map */
void enemy::clearCache()
{
    for(std::unordered_map<characterStatus,animation*>::iterator i = _animationCache.begin(); i != _animationCache.end(); ++i)
        delete i->second;
    _animationCache.erase(_animationCache.begin(), _animationCache.end());
}

/* Updates the status of the enemy */
void enemy::updateStatus(characterStatus status)
{
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

/* Moves the enemy */
void enemy::move()
{
    _y += _currVelocityY;
    _x += _currVelocityX;
    //barrier check
    if (_y > _graphicProc->getResolutionH() * 4 / 5 - _h) {
        _y = _graphicProc->getResolutionH() * 4 / 5 - _h;
        _currVelocityY = 0;
    }
    else {
        _currVelocityY += _velocity;
    }
}

/* Renders the enemy */
void enemy::render() { _animations[_status]->render(_x, _y, _graphicProc, _facing == RIGHT ? 0 : 1); }

/* Seeks the player */
void enemy::seekPlayer(int playerX)
{

    if(playerX < _x) updateStatus(MOVING_LEFT);
    else updateStatus(MOVING_RIGHT);

}

/* Simple accessor functions */
int enemy::getX() { return _x; }
int enemy::getY() { return _y; }
int enemy::getW() { return _w; }
int enemy::getH() { return _h; }
void enemy::updateHealth() { _health--; }
int enemy::checkHealth() { return _health; }
