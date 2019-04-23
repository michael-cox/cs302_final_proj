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
#include "graphics.hpp"

enum buttonReturn { BUTTON_START, BUTTON_EXIT };

enum cursorMovement { CURSOR_UP, CURSOR_DOWN };

struct button
{
    button(const int y, std::string offTexturePath, std::string onTexturePath, imageType imgType,
            buttonReturn returnSignal, graphicProcessor * graphicProc);
    int x, y, w, h;
    graphicProcessor * graphicProc;
    std::pair<SDL_Texture*, SDL_Texture*> textures;
    buttonReturn RETURN_SIGNAL;
    buttonReturn activate();
    void render(bool selected);
};

class menu
{
    private:
        int _cursorPos;
        std::vector<button> _buttons;
        SDL_Texture * _background;
        graphicProcessor * _graphicProc;
        input * _inputProc;
    public:
        menu(graphicProcessor * graphicProc, input * keyInput);
        void moveCursor(cursorMovement direction);
        void render();
        buttonReturn load();
};

#endif
