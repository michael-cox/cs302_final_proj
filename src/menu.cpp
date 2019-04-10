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

void button::render(SDL_Renderer * ren, bool selected)
{
    renderTexture(selected ? textures.second : textures.first, ren, x, y);
}

menu::menu(SDL_Renderer * ren) : cursorPos(0), ren(ren)
{
    
    texture = makeTexture("assets/menu.png", png, ren);

    button start;
    start.x = 450;
    start.y = 250;
    start.textures.first = makeTexture("assets/start.png", png, ren);
    start.textures.second = makeTexture("assets/start_on.png", png, ren);
    SDL_QueryTexture(start.textures.first, NULL, NULL, &start.w, &start.h);
    buttons.push_back(start);

    button exit;
    exit.x = 450;
    exit.y = start.y + 120;
    exit.textures.first = makeTexture("assets/start.png", png, ren);
    exit.textures.second = makeTexture("assets/start_on.png", png, ren);
    SDL_QueryTexture(exit.textures.first, NULL, NULL, &exit.w, &exit.h);
    buttons.push_back(exit);

}

void menu::moveCursor(cursorMovement direction)
{
    if(direction == UP) ++cursorPos;
    else --cursorPos;
    if(cursorPos < 0) cursorPos = buttons.size() - 1;
    if(cursorPos >= buttons.size()) cursorPos = 0;
}

void menu::render()
{
    renderTexture(texture, ren, 0, 0);
    for(size_t i = 0; i < buttons.size(); ++i)
        buttons[i].render(ren, cursorPos == i);
}

buttonReturn menu::menuLoop()
{

    while(1)
    {
        render();

        /* TODO: if up/down pressed, moveCursor(UP/DOWN) */
        /* TODO: if enter pressed, return buttons[cursorPos].activate(); */

    }

}
