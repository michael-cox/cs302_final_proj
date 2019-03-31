/*
 * Michael Cox
 * CS302 March 14, 2019
 * File: game_object.hpp
 * -----------------------
 * An object oriented SDL window
 * handler
 */

#ifndef GAME_OBJ_HPP
#define GAME_OBJ_HPP

#include <SDL2/SDL.h>
#include <map>
#include <string>

enum imageType { bmp, gif, jpg, png };

class GWin
{
    private:
        static bool _isInit;
        SDL_Window * _win;
        SDL_Renderer * _ren;
        SDL_DisplayMode _display;
        std::map<std::string,SDL_Texture* > textures;
    public:

        /* Constructors */
        GWin(std::string windowTitle);
        GWin(std::string windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags);
        /* TODO: GWin(std::string windowTitle, double percentOfScreen, uint32_t windowFlags); */

        /* Deconstructor */
        ~GWin();

        /* SDL initializer */
        void initSDL();

        /* Get display mode */
        void getDisplayMode();

        /* Create window functions */
        void createWindow(std::string windowTitle);
        void createWindow(std::string windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags);
        /* TODO: void createWindow(std::string windowTitle, double percentOfScreen, uint32_t windowFlags); */

        /* Texture importing functions */
        void importIMG(std::string imgPath, imageType imgType);

        /* Render texture */
        void renderTexture(std::string textureName, int x, int y);

        /* Render an animation */
        void renderTextureAnimation(std::string textureName, int frameWidth, int frameNum, int x, int y);

        /* Present render */
        void render();

        /* Run game */
        void runGame();

        /* Main loop */
        void mainLoop();

};

#endif
