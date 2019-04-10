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
#include "object.hpp"

enum buttonReturn { BUTTON_START, BUTTON_EXIT };

enum cursorMovement { UP, DOWN };

struct button
{
    int x, y, w, h;
    std::pair<SDL_Texture*, SDL_Texture*> textures;
    buttonReturn RETURN_SIGNAL;
    buttonReturn activate();
    void render(SDL_Renderer * ren, bool selected);
};

struct menu
{
    int cursorPos;
    SDL_Texture * texture;
    SDL_Renderer * ren;
    std::vector<button> buttons;

    menu(SDL_Renderer * ren);
    void moveCursor(cursorMovement direction);
    void render();
    buttonReturn menuLoop();
    
};

#endif
