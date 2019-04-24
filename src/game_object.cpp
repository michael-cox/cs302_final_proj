#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include "game_object.hpp"

#define GAME_NAME "BRB2D"
#define TILE_W 128
#define TILE_H 128

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
    _graphicProc->renderTextureWithScaling(_background, 0, 0, _w, _h, _graphicProc->getResolutionW(), _graphicProc->getResolutionH());
    for(size_t i = 0; i < _objects.size(); ++i)
    {
        _objects[i]->render();
    }
}

void game::runGame()
{
    placeWall(0, _graphicProc->getResolutionH() * 2 / 3, LEFT_EDGE);
    for(size_t i = TILE_W; i < _graphicProc->getResolutionW() - TILE_W; i += TILE_W)
        placeWall(i, _graphicProc->getResolutionH() * 2 / 3, CENTER);
    placeWall(_graphicProc->getResolutionW() - TILE_W, _graphicProc->getResolutionH() * 2 / 3, RIGHT_EDGE);
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
    while(1)
    {
        render();
        _player->render();
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
        }
        _player->move();
    }
}

void game::placeWall(int x, int y, wallType type)
{
    wall * newWall;
    switch(type)
    {
        case LEFT_EDGE:
            newWall = new wall(x, y, TILE_W, TILE_H, _graphicProc, "assets/wintertileset/png/tiles/1.png", PNG);
            break;
        case CENTER:
            newWall = new wall(x, y, TILE_W, TILE_H, _graphicProc, "assets/wintertileset/png/tiles/2.png", PNG);
            break;
        case RIGHT_EDGE:
            newWall = new wall(x, y, TILE_W, TILE_H, _graphicProc, "assets/wintertileset/png/tiles/3.png", PNG);
            break;
    }

    for(int i = newWall->_y; i < newWall->_y + newWall->_h; ++i)
    {
        for(int j = newWall->_x; j < newWall->_x + newWall->_w; ++j)
        {
            _map->gameMap[i][j].first = true;
            _map->gameMap[i][j].second.push_back(newWall);
        }
    }

    _objects.push_back(newWall);
}
