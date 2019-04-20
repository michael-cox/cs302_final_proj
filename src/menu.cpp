/*
 * File: menu.cpp
 * Michael Cox
 * --------------
 * Implements the menu object.
 */

#include "menu.hpp"
#include "image.hpp"
#include "input.hpp"

buttonReturn button::activate()
{
    return RETURN_SIGNAL;
}

void button::render(imageProcessor * imgProc, bool selected)
{
    imgProc->renderTexture(selected ? textures.second : textures.first, x, y, w, h);
}

menu::menu(imageProcessor * img, input * inputProc) : cursorPos(0), imgProc(img), keyInput(inputProc)
{
    
    SDL_Log("Constructing menu...");

    texture = imgProc->makeTexture("assets/bg.png", png);

    button start;
    start.x = 450;
    start.y = 250;
    start.RETURN_SIGNAL = BUTTON_START;
    start.textures.first = imgProc->makeTexture("assets/start.png", png);
    start.textures.second = imgProc->makeTexture("assets/start_on.png", png);
    SDL_QueryTexture(start.textures.first, NULL, NULL, &start.w, &start.h);
    buttons.push_back(start);

    button exit;
    exit.x = 450;
    exit.y = start.y + 120;
    exit.RETURN_SIGNAL = BUTTON_EXIT;
    exit.textures.first = imgProc->makeTexture("assets/start.png", png);
    exit.textures.second = imgProc->makeTexture("assets/start_on.png", png);
    SDL_QueryTexture(exit.textures.first, NULL, NULL, &exit.w, &exit.h);
    buttons.push_back(exit);

    SDL_Log("Finished constructing menu");

}

void menu::moveCursor(cursorMovement direction)
{
    if(direction == CURSOR_UP) ++cursorPos;
    else --cursorPos;
    if(cursorPos < 0) cursorPos = buttons.size() - 1;
    if(cursorPos >= buttons.size()) cursorPos = 0;
}

void menu::render()
{
    SDL_Log("Rendering menu...");
    imgProc->renderTexture(texture, 0, 0, 1440, 780);
    for(size_t i = 0; i < buttons.size(); ++i)
        buttons[i].render(imgProc, cursorPos == i);
    imgProc->present();
    SDL_Log("Finished rendering menu.");
}

buttonReturn menu::menuLoop()
{
	SDL_Keycode key;
    while(1)
    {
        render();
		key = keyInput->readInput();
		switch (key) {
			case SDLK_UP:
				if (keyInput->readDirection()) { moveCursor(CURSOR_UP); }
				break;
			case SDLK_DOWN:
				if (keyInput->readDirection()) { moveCursor(CURSOR_DOWN); }
				break;
			case SDLK_RETURN:
				if (keyInput->readDirection()) { return buttons[cursorPos].activate(); }
		}
    }

}