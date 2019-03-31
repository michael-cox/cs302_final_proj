#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

void GWin::importIMG(std::string imgPath, imageType imgType)
{
    SDL_RWops * fStream = SDL_RWFromFile(imgPath.c_str(), "rb");
    SDL_Surface * renderSurface;
    switch(imgType)
    {
        case bmp:
            renderSurface = IMG_LoadBMP_RW(fStream);
            break;
        case gif:
            renderSurface = IMG_LoadGIF_RW(fStream);
            break;
        case jpg:
            renderSurface = IMG_LoadJPG_RW(fStream);
            break;
        case png:
            renderSurface = IMG_LoadPNG_RW(fStream);
            break;
    }
    SDL_Texture * imgTexture = SDL_CreateTextureFromSurface(_ren, renderSurface);
    textures[imgPath] = imgTexture;
}

void GWin::renderTexture(std::string textureName, int x, int y)
{
    std::map<std::string, SDL_Texture * >::iterator texturePair = textures.find(textureName);
    assert(texturePair != textures.end());
    SDL_Texture * imgTexture = texturePair->second;
    SDL_Rect sourceRect, destRect;
    SDL_QueryTexture(imgTexture, NULL, NULL, &sourceRect.w, &sourceRect.h);
    destRect.w = sourceRect.w;
    destRect.h = sourceRect.h;
    sourceRect.x = sourceRect.y = 0;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopy(_ren, imgTexture, &sourceRect, &destRect);
}

void GWin::renderTextureAnimation(std::string textureName, int frameWidth, int frameNum, int x, int y)
{
    int maxWidth;
    std::map<std::string, SDL_Texture * >::iterator texturePair = textures.find(textureName);
    assert(texturePair != textures.end());
    SDL_Texture * imgTexture = texturePair->second;
    SDL_Rect sourceRect, destRect;
    SDL_QueryTexture(imgTexture, NULL, NULL, &maxWidth, &sourceRect.h);
    destRect.w = sourceRect.w = frameWidth;
    destRect.h = sourceRect.h;
    sourceRect.x = frameNum * frameWidth;
    assert(sourceRect.x + frameWidth < maxWidth);
    sourceRect.y = 0;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopy(_ren, imgTexture, &sourceRect, &destRect);
}

void GWin::render()
{
    SDL_RenderPresent(_ren);
}

void GWin::runGame()
{
    SDL_SetRenderDrawColor(_ren, 255, 0, 0, 0);
    importIMG("assets/skeleton/spritesheets/attack.png", png);
    for(int i = 0; i < 8; ++i)
    {
        renderTextureAnimation("assets/skeleton/spritesheets/attack.png", 43, i, 5, 5);
        render();
        SDL_Delay(50);
        SDL_RenderClear(_ren);
    }
    SDL_Delay(2000);
}
