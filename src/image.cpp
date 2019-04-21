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
#include "image.hpp"

imageProcessor::imageProcessor(SDL_Renderer * ren) : _renderer(ren) {}

SDL_Texture * imageProcessor::makeTexture(const std::string imgPath, const imageType imgType)
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
    SDL_Texture * imgTexture = SDL_CreateTextureFromSurface(_renderer, renderSurface);
    return imgTexture;
}

void imageProcessor::renderTexture(SDL_Texture * texture, const int x, const int y, const int w, const int h)
{
    SDL_Rect sourceRect, destRect;
    destRect.w = sourceRect.w = w;
    destRect.h = sourceRect.h = h;
    sourceRect.x = sourceRect.y = 0;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopy(_renderer, texture, &sourceRect, &destRect);
}

void imageProcessor::renderTextureWithScaling(SDL_Texture * texture, const int x, const int y,
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

void imageProcessor::renderTextureAnimation(SDL_Texture * texture, int frameWidth, int frameNum, int x, int y)
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
}

void imageProcessor::present() { SDL_RenderPresent(_renderer); }
