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

/* Enum to give image types */
enum imageType { BMP, GIF, JPG, PNG };

/* ENUM for whether to launch full screen or smaller */
enum windowMode { FULLSCREEN, SMALL };

/* A struct for static textures that is slightly nicer than SDL's textures */
struct sprite
{
    sprite(std::string filename, imageType imgType, int w, int h, class graphicProcessor * graphicProc);
    ~sprite();
    void render(const int x, const int y, class graphicProcessor * graphicProc);

    SDL_Texture * texture;
    int w, h, scaledW, scaledH;
};

/* A struct for stylesheet style animations */
struct styleSheet
{
    SDL_Texture * spriteSheet;
    int frameWidth;
    size_t frameNum;
    size_t numFrames;
};

/* A struct for separate file animations... assumes a naming scheme of filename0.png
 * where you pass baseFilename as just filename */
struct animation
{
    animation(std::string baseFilename, imageType imgType, size_t framesPerTexture, size_t numImages, int w, int h, class graphicProcessor * graphicProc);
    ~animation();
    bool render(const int x, const int y, class graphicProcessor * graphicProc, bool reverse);
    std::vector<SDL_Texture*> textures;
    int h, w, scaledW, scaledH;
    size_t curFrame, framesPerTexture, numFrames;
};

/* Object oriented graphics processor */
class graphicProcessor
{
    private:

        SDL_Window * _window;
        SDL_Renderer * _renderer;
        SDL_DisplayMode * _display;

        /* Statics that determine when to init/quit SDL
         * if you were to create multiple windows */
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

        void clear();

        /* Make texture */
        SDL_Texture * makeTexture(const std::string imgPath, const imageType imgType);

        /* Different renderning functions */
        void renderSprite(sprite * spriteToRender, const int x, const int y);
        void renderTexture(SDL_Texture * imgTexture, const int x, const int y, const int w, const int h);
        void renderTextureWithScaling(SDL_Texture * imgTexture, const int x, const int y, const int sourceW, const int sourceH, const int w, const int h, bool reverse);
        void renderAnimation(animation anim, const int x, const int y);
        
        /* Just presents the render */
        void present();
};

#endif
