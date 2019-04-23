/*
 * File: menu.cpp
 * Michael Cox
 * --------------
 * Implements the menu object.
 */

#include "menu.hpp"
#include "image.hpp"
#include "input.hpp"
#include "sound.hpp"

button::button(const int y, std::string offTexturePath, std::string onTexturePath, imageType imgType, 
        buttonReturn returnSignal, graphicProcessor * graphicProc)
    : y(y), RETURN_SIGNAL(returnSignal), graphicProc(graphicProc)
{
    textures.first = graphicProc->makeTexture(offTexturePath, imgType);
    textures.second = graphicProc->makeTexture(onTexturePath, imgType);
    SDL_QueryTexture(textures.first, NULL, NULL, &w, &h);
    x = graphicProc->getResolutionW() / 2 - w / 2;
}

buttonReturn button::activate() { return RETURN_SIGNAL; }

void button::render(bool selected)
{
    graphicProc->renderTexture(selected ? textures.second : textures.first, x, y, w, h);
}

menu::menu(graphicProcessor * graphicProc, input * inputProc) : _cursorPos(0),
    _graphicProc(graphicProc), _inputProc(inputProc)
{
    
    SDL_Log("Constructing menu...");

    _background = _graphicProc->makeTexture("assets/menu/winter.png", PNG);

    button start(250, "assets/menu/buttons/start_off.png", "assets/menu/buttons/start_on.png", PNG, BUTTON_START, _graphicProc);
    _buttons.push_back(start);

    button exit(250 + 120, "assets/menu/buttons/exit_off.png", "assets/menu/buttons/exit_on.png", PNG, BUTTON_EXIT, _graphicProc);
    _buttons.push_back(exit);

    SDL_Log("Finished constructing menu");

}

void menu::moveCursor(cursorMovement direction)
{
    if(direction == CURSOR_UP) ++_cursorPos;
    else --_cursorPos;
    if(_cursorPos < 0) _cursorPos = _buttons.size() - 1;
    if(_cursorPos >= _buttons.size()) _cursorPos = 0;
}

void menu::render()
{
    _graphicProc->renderTexture(_background, 0, 0, _graphicProc->getResolutionW(), _graphicProc->getResolutionH());
    for(size_t i = 0; i < _buttons.size(); ++i)
    {
        _buttons[i].render(_cursorPos == i);
    }
    _graphicProc->present();
}

buttonReturn menu::load()
{
	soundProcessor sound;
	sound.playSound("assets/sounds/menu.wav");
    while(1)
    {
        render();
		if (sound.checkQueue() == 0) { sound.repeat(); }
		switch (_inputProc->readInput()) {
			case SDLK_UP:
				if (_inputProc->readDirection()) { moveCursor(CURSOR_UP); }
				break;
			case SDLK_DOWN:
				if (_inputProc->readDirection()) { moveCursor(CURSOR_DOWN); }
				break;
			case SDLK_RETURN:
				if (_inputProc->readDirection()) { 
					sound.stopSound();
					return _buttons[_cursorPos].activate();
                }
		}
    }

}
