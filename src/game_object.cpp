#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include "game_object.hpp"

#define GAME_NAME "BRB2D"
#define TILE_W 64
#define TILE_H 64

game::game(windowMode winMode)
{
    if(winMode == FULLSCREEN) _graphicProc = new graphicProcessor(GAME_NAME);
    else _graphicProc = new graphicProcessor(GAME_NAME, 1024, 576, 0);
    _inputProc = new input;
	_soundProc = new soundProcessor;
    _mainMenu = new menu(_graphicProc, _inputProc, _soundProc);
    _map = new map(_graphicProc->getResolutionW(), _graphicProc->getResolutionH());
    _background = _graphicProc->makeTexture("assets/winter.png", PNG);
    SDL_QueryTexture(_background, NULL, NULL, &_w, &_h);
    _player = new player("Player", _graphicProc->getResolutionW() / 2, 20, _graphicProc, _soundProc);

	_enemy = new enemy("Enemy", _graphicProc->getResolutionW() / 2, 20, _graphicProc, _soundProc);

}

game::~game()
{
    delete _graphicProc;
    delete _inputProc;
	delete _soundProc;
    delete _mainMenu;
}

void game::render()
{
    _graphicProc->clear();
    _graphicProc->renderTextureWithScaling(_background, 0, 0, _w, _h, _graphicProc->getResolutionW(), _graphicProc->getResolutionH(), false);
    for(size_t i = 0; i < _objects.size(); ++i)
    {
        _objects[i]->render();
    }
}

void game::runGame()
{
    for(size_t i = 0; i < _graphicProc->getResolutionW(); i += TILE_W)
        placeWall(i, _graphicProc->getResolutionH() * 4 / 5, CENTER_SNOW);
    for(size_t i = _graphicProc->getResolutionH() * 4 / 5 + TILE_H; i < _graphicProc->getResolutionH(); i += TILE_H)
    {
        for(size_t j = 0; j < _graphicProc->getResolutionW(); j += TILE_W)
        {
            placeWall(j, i, CENTER_DIRT);
        }
    }
    while(1)
    {
        if(_mainMenu->load() == BUTTON_EXIT) return;
        _soundProc->playSound("gameStart.wav");
        mainLoop();
    }
}

void game::mainLoop()
{
    _soundProc->playSound("gameMusic.wav");
	_player->updateStatus(IDLE);
    while(1)
    {
        render();
        _player->render();
		_enemy->render();

        _graphicProc->present();
        if (_soundProc->checkQueue("gameMusic.wav") == 0) { _soundProc->repeat("gameMusic.wav"); }
        switch(_inputProc->readInput())
        {
            case SDLK_SPACE:
                if(_inputProc->readDirection())
                {
                    _player->updateStatus(JUMP);
                }
                break;
            case SDLK_LEFT:
                if(_inputProc->readDirection())
                {
                    _player->updateStatus(MOVING_LEFT);
                } else _player->updateStatus(MOVING_RIGHT);
                break;
            case SDLK_RIGHT:
                if(_inputProc->readDirection())
                {
                    _player->updateStatus(MOVING_RIGHT);
                } else _player->updateStatus(MOVING_LEFT);
                break;
            case SDLK_z:
                if (_inputProc->readDirection()) {
                    _player->updateStatus(ATTACK);
                }
                break;
            case SDLK_ESCAPE:
                if(_inputProc->readDirection()) { _soundProc->stopSound("gameMusic.wav"); return; }
                break;
			default:
				break;
        }
        _player->move();

        _enemy->seekPlayer(_player->getX());
		_enemy->move();

    }
}

void game::placeWall(int x, int y, wallType type)
{
    wall * newWall;
    switch(type)
    {
        case LEFT_EDGE_SNOW:
            newWall = new wall(x, y, TILE_W, TILE_H, _graphicProc, "assets/wintertileset/png/tiles/1.png", PNG);
            break;
        case CENTER_SNOW:
            newWall = new wall(x, y, TILE_W, TILE_H, _graphicProc, "assets/wintertileset/png/tiles/2.png", PNG);
            break;
        case RIGHT_EDGE_SNOW:
            newWall = new wall(x, y, TILE_W, TILE_H, _graphicProc, "assets/wintertileset/png/tiles/3.png", PNG);
            break;
        case CENTER_DIRT:
            newWall = new wall(x, y, TILE_W, TILE_H, _graphicProc, "assets/wintertileset/png/tiles/5.png", PNG);
            break;
    }

    for(int i = newWall->_y; i < newWall->_y + newWall->_h; ++i)
    {
        for(int j = newWall->_x; j < newWall->_x + newWall->_w; ++j)
        {
            if(i < _map->gameMap.size() && j < _map->gameMap[0].size())
            {
                _map->gameMap[i][j].first = true;
                _map->gameMap[i][j].second.push_back(newWall);
            }
        }
    }

    _objects.push_back(newWall);
}
