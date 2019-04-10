/*
 * File: image.hpp
 * Michael Cox
 * ---------------
 * Interface for loading images.
 */

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <SDL2/SDL.h>
#include <string>

enum imageType { bmp, gif, jpg, png };

struct animation
{
    SDL_Texture * spriteSheet;
    size_t frameWidth;
    size_t frameNum;
    size_t numFrames;
};

class imageProcessor
{
    private:
        SDL_Renderer * _renderer;
    public:
        imageProcessor(SDL_Renderer * ren);
        SDL_Texture * makeTexture(const std::string imgPath, const imageType imgType, SDL_Renderer * ren);
        void renderTexture(SDL_Texture * imgTexture, SDL_Renderer * ren, int x, int y, int w, int h);
};

#endif
