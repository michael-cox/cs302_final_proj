/*
 * File: graphics.hpp
 * Michael Cox
 * ---------------
 * Interface for loading images.
 */

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SDL2/SDL.h>
#include <string>
#include <vector>

enum imageType { BMP, GIF, JPG, PNG };

enum windowMode { FULLSCREEN, SMALL };

struct styleSheet
{
    SDL_Texture * spriteSheet;
    int frameWidth;
    size_t frameNum;
    size_t numFrames;
};

struct animation
{
    std::vector<SDL_Texture*> textures;
    int h, w, scaledW, scaledH;
    size_t curFrame, numFrames;
};

class graphicProcessor
{
    private:

        SDL_Window * _window;
        SDL_Renderer * _renderer;
        SDL_DisplayMode * _display;
        static size_t _numInst;
        static bool _isInit;

        /* SDL initializer */
        void initSDL();

        /* Get display mode */
        void getDisplayMode();

        /* Create window functions */
        void createWindow(std::string windowTitle);
        void createWindow(std::string windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags);

    public:

        /* Constructors */
        graphicProcessor(std::string windowTitle);
        graphicProcessor(std::string windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags);

        /* Deconstructor */
        ~graphicProcessor();

        /* Resolution getters */
        int getResolutionW() const;
        int getResolutionH() const;

        /* Make texture */
        SDL_Texture * makeTexture(const std::string imgPath, const imageType imgType);

        void renderTexture(SDL_Texture * imgTexture, const int x, const int y, const int w, const int h);
        void renderTextureWithScaling(SDL_Texture * imgTexture, const int x, const int y, const int sourceW, const int sourceH, const int w, const int h);
        void renderTextureAnimation(SDL_Texture * texture, int frameWidth, int frameNum, int x, int y);
        void present();
};

#endif
