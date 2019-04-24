/*
 * File: image.cpp
 * Michael Cox
 * ---------------
 * Implements functions for loading
 * images from image.hpp.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include "graphics.hpp"

bool graphicProcessor::_isInit = 0;

size_t graphicProcessor::_numInst = 0;

sprite::sprite(std::string filename, imageType imgType, int width, int height, graphicProcessor * graphicProc)
    : scaledW(width), scaledH(height)
{
    texture = graphicProc->makeTexture(filename, imgType);
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

sprite::~sprite() { delete texture; }

void sprite::render(const int x, const int y, class graphicProcessor * graphicProc)
{
    graphicProc->renderTextureWithScaling(texture, x, y, w, h, scaledW, scaledH);
}

animation::animation(std::string baseFilename, imageType imgType, size_t framesPerTexture, size_t numFrames, int width, int height, graphicProcessor * graphicProc)
    : scaledW(width), scaledH(height), numFrames(numFrames), curFrame(0), framesPerTexture(framesPerTexture)
{
    for(size_t i = 0; i < numFrames; ++i)
    {
        std::string filename = baseFilename + std::to_string(i);
        switch(imgType)
        {
            case BMP:
                filename += ".bmp";
                break;
            case GIF:
                filename += ".gif";
                break;
            case JPG:
                filename += ".jpg";
                break;
            case PNG:
                filename += ".png";
                break;
        }
        SDL_Log("%s", filename.c_str());
        SDL_Texture * texture = graphicProc->makeTexture(filename, imgType);
        textures.push_back(texture);
    }
    SDL_QueryTexture(textures[0], NULL, NULL, &w, &h);
}

animation::~animation()
{
    for(size_t i = 0; i < textures.size(); ++i)
        delete textures[i];
}

void animation::render(const int x, const int y, class graphicProcessor * graphicProc)
{
    graphicProc->renderTextureWithScaling(textures[curFrame / framesPerTexture], x, y, w, h, scaledW, scaledH);
    if(++curFrame > textures.size() * framesPerTexture) curFrame = 0;
}

graphicProcessor::graphicProcessor(std::string windowTitle) : _window(nullptr), _renderer(nullptr),
    _display(nullptr)
{
    SDL_Log("Constructing graphicProcessor...");
    initSDL();
    createWindow(windowTitle);
    if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) SDL_Log("Set scaling hint.");
    SDL_Log("Finished constructing graphicProcessor");
}

graphicProcessor::graphicProcessor(std::string windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags)
    : _window(nullptr), _renderer(nullptr), _display(nullptr)
{
    SDL_Log("Constructing graphicProcessor...");
    initSDL();
    createWindow(windowTitle, windowWidth, windowHeight, windowFlags);
    if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) SDL_Log("Set scaling hint.");
    _display->w = windowWidth;
    _display->h = windowHeight;
    SDL_Log("Finished constructing graphicProcessor");
}


graphicProcessor::~graphicProcessor()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    delete _display;
    --_numInst;
    SDL_Log("_numInst (after destructing): %zu", _numInst);
    if(!_numInst) { SDL_Log("Quitting SDL..."); SDL_Quit(); }
}

void graphicProcessor::clear() { SDL_RenderClear(_renderer); }

void graphicProcessor::initSDL()
{
    if(!_isInit)
    {
        SDL_Log("Initializing SDL...");
        if(SDL_Init(SDL_INIT_EVERYTHING))
            SDL_Log("Failed to initialize SDL. Error: %s", SDL_GetError());
        getDisplayMode();
        _isInit = 1;
        SDL_Log("Finished initializing SDL");
    }
    ++_numInst;
    SDL_Log("_numInst (after constructing): %zu", _numInst);
}

void graphicProcessor::getDisplayMode()
{
    SDL_Log("Getting display mode...");
    if(_display == nullptr) _display = new SDL_DisplayMode;
    if(SDL_GetCurrentDisplayMode(0, _display))
    {
        SDL_Log("Failed to get display mode. Error: %s", SDL_GetError());
    }
    SDL_Log("Display mode: %dx%d %d Hz", _display->w, _display->h, _display->refresh_rate);
}

void graphicProcessor::createWindow(std::string windowTitle)
{
    SDL_Log("Creating window...");
    _window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            _display->w, _display->h, SDL_WINDOW_FULLSCREEN);
    assert(_window != nullptr);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
    assert(_renderer != nullptr);
    SDL_Log("Finished creating window.");
}

void graphicProcessor::createWindow(std::string windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags)
{
    SDL_Log("Creating window...");
    _window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            windowWidth, windowHeight, windowFlags);
    assert(_window != nullptr);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
    assert(_renderer != nullptr);
    SDL_Log("Finished creating window.");
}

int graphicProcessor::getResolutionW() const { return _display->w; }
int graphicProcessor::getResolutionH() const { return _display->h; }

SDL_Texture * graphicProcessor::makeTexture(const std::string imgPath, const imageType imgType)
{
    SDL_RWops * fStream = SDL_RWFromFile(imgPath.c_str(), "rb");
    SDL_Surface * renderSurface;
    switch(imgType)
    {
        case BMP:
            renderSurface = IMG_LoadBMP_RW(fStream);
            break;
        case GIF:
            renderSurface = IMG_LoadGIF_RW(fStream);
            break;
        case JPG:
            renderSurface = IMG_LoadJPG_RW(fStream);
            break;
        case PNG:
            renderSurface = IMG_LoadPNG_RW(fStream);
            break;
    }
    SDL_Texture * imgTexture = SDL_CreateTextureFromSurface(_renderer, renderSurface);
    delete renderSurface;
    return imgTexture;
}

void graphicProcessor::renderTexture(SDL_Texture * texture, const int x, const int y, const int w, const int h)
{
    SDL_Rect sourceRect, destRect;
    destRect.w = sourceRect.w = w;
    destRect.h = sourceRect.h = h;
    sourceRect.x = sourceRect.y = 0;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopy(_renderer, texture, &sourceRect, &destRect);
}

void graphicProcessor::renderTextureWithScaling(SDL_Texture * texture, const int x, const int y,
        const int sourceW, const int sourceH, const int w, const int h)
{
    SDL_Rect sourceRect, destRect;
    destRect.w = w;
    sourceRect.w = sourceW;
    destRect.h = h;
    sourceRect.h = sourceH;
    sourceRect.x = sourceRect.y = 0;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopy(_renderer, texture, &sourceRect, &destRect);
}

void graphicProcessor::renderSprite(sprite * spriteToRender, const int x, const int y)
{
    SDL_Rect sourceRect, destRect;
    destRect.w = spriteToRender->scaledW;
    sourceRect.w = spriteToRender->w;
    destRect.h = spriteToRender->scaledH;
    sourceRect.h = spriteToRender->h;
    sourceRect.x = sourceRect.y = 0;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopy(_renderer, spriteToRender->texture, &sourceRect, &destRect);
}

/*void graphicProcessor::renderTextureAnimation(SDL_Texture * texture, int frameWidth, int frameNum, int x, int y)
{
    int maxWidth;
    SDL_Rect sourceRect, destRect;
    SDL_QueryTexture(texture, NULL, NULL, &maxWidth, &sourceRect.h);
    destRect.w = sourceRect.w = frameWidth;
    destRect.h = sourceRect.h;
    sourceRect.x = frameNum * frameWidth;
    assert(sourceRect.x + frameWidth < maxWidth);
    sourceRect.y = 0;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopy(_renderer, texture, &sourceRect, &destRect);
}*/

void graphicProcessor::present() { SDL_RenderPresent(_renderer); }
