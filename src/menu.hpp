/*
 * File: menu.hpp
 * Michael Cox
 * --------------
 * Provides an interface for loading menus.
 */

#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <utility>
#include <string>
#include "input.hpp"
#include "image.hpp"

enum buttonReturn { BUTTON_START, BUTTON_EXIT };

enum cursorMovement { CURSOR_UP, CURSOR_DOWN };

struct button
{
    int x, y, w, h;
    std::pair<SDL_Texture*, SDL_Texture*> textures;
    buttonReturn RETURN_SIGNAL;
    buttonReturn activate();
    void render(imageProcessor * imgProc, bool selected);
};

struct menu
{
    int cursorPos;
    SDL_Texture * texture;
    imageProcessor * imgProc;
    input * keyInput;
    std::vector<button> buttons;

    menu(imageProcessor * img, input * inputProc);
    void moveCursor(cursorMovement direction);
    void render();
    buttonReturn menuLoop();
    
};

#endif
