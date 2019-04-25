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
#include "sound.hpp"

/* buttonReturn - enum of button return signals */
enum buttonReturn { BUTTON_START, BUTTON_EXIT };

/* cursorMovement - enum of directions a cursor can move */
enum cursorMovement { CURSOR_UP, CURSOR_DOWN };

struct button
{

    /* Constructs a button in the middle of the screen with textures for both selected and
     * unselected modes */
    button(const int y, std::string offTexturePath, std::string onTexturePath, imageType imgType,
            buttonReturn returnSignal, graphicProcessor * graphicProc);
    int x, y, w, h;
    graphicProcessor * graphicProc;
    std::pair<SDL_Texture*, SDL_Texture*> textures;
    buttonReturn RETURN_SIGNAL;

    /* activate - returns the return signal */
    buttonReturn activate();

    /* render - copies the button to the screen */
    void render(bool selected);

};

class menu
{

    private:

        int _cursorPos;
        int _w, _h;
        std::vector<button> _buttons;
        SDL_Texture * _background;
        graphicProcessor * _graphicProc;
        input * _inputProc;
		soundProcessor * _soundProc;

    public:

        /* Constructor */
        menu(graphicProcessor * graphicProc, input * keyInput, soundProcessor * soundProc);

        /* moveCursor - moves the cursor in the specified direction */
        void moveCursor(cursorMovement direction);

        /* render - places the screen and all of the buttons on the screen */
        void render();
        buttonReturn load();
};

#endif
