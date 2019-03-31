#include <SDL2/SDL.h>
#include <cassert>
#include "window_object.hpp"

bool GWin::_isInit = 0;

GWin::GWin(std::string windowTitle)
{
    initSDL();
    createWindow(windowTitle);
}

GWin::GWin(std::string windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags)
{
    initSDL();
    createWindow(windowTitle, windowWidth, windowHeight, windowFlags);
}

/* TODO: Constructor with percent size
GWin::GWin(std::string windowTitle, double percentOfScreen, uint32_t windowFlags)
{
    initSDL();
    createWindow(windowTitle, percentOfScreen, windowFlags);
}
*/

GWin::~GWin()
{
    SDL_DestroyWindow(_win);
    SDL_DestroyRenderer(_ren);
}

void GWin::initSDL()
{
    if(!_isInit)
    {
        if(SDL_Init(SDL_INIT_EVERYTHING))
            SDL_Log("Failed to initialize SDL. Error: %s", SDL_GetError());
        getDisplayMode();
        _isInit = 1;
    }
}

void GWin::getDisplayMode()
{
    if(SDL_GetCurrentDisplayMode(0, &_display))
    {
        SDL_Log("Failed to get display mode. Error: %s", SDL_GetError());
    }
}

void GWin::createWindow(std::string windowTitle)
{
    _win = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            _display.w, _display.h, SDL_WINDOW_FULLSCREEN);
    assert(_win != nullptr);
    _ren = SDL_CreateRenderer(_win, -1, 0);
    assert(_ren != nullptr);
}

void GWin::createWindow(std::string windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags)
{
    _win = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            windowWidth, windowHeight, windowFlags);
    assert(_win != nullptr);
    _ren = SDL_CreateRenderer(_win, -1, 0);
    assert(_ren != nullptr);
}

/* TODO: createWindow with percent size
void GWin::createWindow(std::string windowTitle, double percentOfScreen, uint32_t windowFlags)
{
}
*/

SDL_Texture * GWin::loadBMP(std::string imagePath, int x, int y)
{
    SDL_Surface * renderSurface = SDL_LoadBMP(imagePath.c_str());
    assert(renderSurface != nullptr);
    SDL_Texture * texture;
    texture = SDL_CreateTextureFromSurface(_ren, renderSurface);

    SDL_Rect sourceRect, destRect;
    SDL_QueryTexture(texture, NULL, NULL, &sourceRect.w, &sourceRect.h);

    destRect.w = sourceRect.w;
    destRect.h = sourceRect.h;
    destRect.x = sourceRect.x = x;
    destRect.y = sourceRect.y = y;

    SDL_RenderCopy(_ren, texture, &sourceRect, &destRect);
    SDL_RenderPresent(_ren);

    return texture;
}

void GWin::renderStyleSheet(std::string ssPath, int frameWidth, int x, int y)
{
}

void GWin::runGame()
{
    loadBMP("assets/char.bmp", 0, 0);
    SDL_Delay(2000);
}
