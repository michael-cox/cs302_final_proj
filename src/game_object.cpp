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
    else _graphicProc = new graphicProcessor(GAME_NAME, 1024, 576, 0);
    _inputProc = new input;
    _mainMenu = new menu(_graphicProc, _inputProc);
    _map = new map(_graphicProc->getResolutionW(), _graphicProc->getResolutionH());
    _background = _graphicProc->makeTexture("assets/winter.png", PNG);
    SDL_QueryTexture(_background, NULL, NULL, &_w, &_h);
}

game::~game()
{
    delete _graphicProc;
    delete _inputProc;
    delete _mainMenu;
}

void game::render()
{
    _graphicProc->renderTextureWithScaling(_background, 0, 0, _w, _h, _graphicProc->getResolutionW(), _graphicProc->getResolutionH());
}

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
    player p("Player", _graphicProc->getResolutionW() / 2, 20, _graphicProc);

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
                if(_inputProc->readDirection()) return;
                break;
        }
        p.move();
    }
}
