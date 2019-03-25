#include <SDL2/SDL.h>
#include <iostream>

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 700, NULL);
    SDL_Renderer * render = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface * charSurf;
    SDL_Texture * character;
    SDL_Rect charRect;
    SDL_Rect destRect;

    charSurf = SDL_LoadBMP("assets/char.bmp");
    character = SDL_CreateTextureFromSurface(render, charSurf);
    SDL_FreeSurface(charSurf);
    SDL_QueryTexture(character, NULL, NULL, &charRect.w, &charRect.h);
    destRect.x = charRect.x = 0;
    destRect.y = charRect.y = 0;
    destRect.w = charRect.w;
    destRect.h = charRect.h;

    while(1)
    {
        SDL_RenderCopy(render, character, &charRect, &destRect);
        SDL_RenderPresent(render);

        SDL_Delay(5000);

        SDL_RenderClear(render);
        ++destRect.x;
        ++destRect.y;
    }

    SDL_Quit();

    return 0;
}
