#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include <fstream>
#include "menu.hpp"
#include "game_object.hpp"
#include "map.hpp"
#include "character.hpp"

#define GAME_NAME "BRB2D"

game::game(windowMode winMode)
{
    if(winMode == FULLSCREEN) _graphicProc = new graphicProcessor(GAME_NAME);
    else _graphicProc = new graphicProcessor(GAME_NAME, 800, 450, 0);
    _inputProc = new input;
    _mainMenu = new menu(_graphicProc, _inputProc);
    _background = _graphicProc->makeTexture("assets/winter.png", PNG);
}

game::~game()
{
    delete _graphicProc;
    delete _inputProc;
    delete _mainMenu;
}

void game::render()
{
    _graphicProc->renderTexture(_background, 0, 0, _graphicProc->getResolutionW(), _graphicProc->getResolutionH());
}

/*
void game::loadMapFromText(std::string filename)
{
    std::ifstream mapStream;
    if(_map != nullptr)
    {
        SDL_Log("Map already exists... deleting...");
        delete _map;
    }
    SDL_Log("Constructing map...");
    _map = new Map(_display->w, _display->h);
    SDL_Log("Constructed map.");
    mapStream.open(filename);
    if(mapStream.fail())
    {
        SDL_Log("Failed to open file %s.", filename.c_str());
    }
    char tileType;
    size_t x, y, w, h;
    while(mapStream >> tileType >> w >> h >> x >> y)
    {
        SDL_Log("%c %zu %zu %zu %zu", tileType, w, h, x, y);
        for(size_t i = y; i < y + h; ++i)
        {
            for(size_t j = x; j < x + w; ++j)
            {
                if(i < _map->_width && j < _map->_height)
                    _map->_map[i * _map->_width + j] = tileType;
            }
        }
    }
}

void GWin::dumpMap()
{
    std::string output;
    for(size_t i = 0; i < _map->_width * _map->_height; ++i)
    {
        if(!(i % _map->_width))
        {
            SDL_Log("%s", output.c_str());
            output = "";
        }
        if(_map->_map[i] == 0) output += '-';
        else output += _map->_map[i];
    }
    SDL_Log("%s", output.c_str());
}
*/

void game::runGame()
{
    while(1)
    {
        if(_mainMenu->load() == BUTTON_EXIT) return;
        mainLoop();
    }
}

void game::mainLoop()
{
    player p("Player", 15, 20, _graphicProc);

    while(1)
    {
        render();
        p.render();
        _graphicProc->present();
        switch(_inputProc->readInput())
        {
            case SDLK_SPACE:
                if(_inputProc->readDirection())
                {
                    p.updateStatus(JUMP);
                }
                break;
            case SDLK_LEFT:
                if(_inputProc->readDirection())
                {
                    p.updateStatus(MOVING_LEFT);
                } else p.updateStatus(MOVING_RIGHT);
                break;
            case SDLK_RIGHT:
                if(_inputProc->readDirection())
                {
                    p.updateStatus(MOVING_RIGHT);
                } else p.updateStatus(MOVING_LEFT);
                break;
            case SDLK_ESCAPE:
                if(_inputProc->readDirection())
                {
                    SDL_Log("Got return");
                    return;
                }
                break;
        }
        p.move();
    }
}
