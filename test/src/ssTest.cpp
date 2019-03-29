#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char** argv)
{

    int maxW, maxH;
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window * win = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, 0);

    SDL_Renderer * ren = SDL_CreateRenderer(win, -1, 0);

    SDL_Rect sourceRect;
    SDL_Rect destRect;

    SDL_Surface * surf = SDL_LoadBMP("assets/skeleton/spritesheets/attack.bmp");
    SDL_Texture * texture = SDL_CreateTextureFromSurface(ren, surf);
    SDL_FreeSurface(surf);
    SDL_QueryTexture(texture, NULL, NULL, &maxW, &sourceRect.h);

    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);

    std::cout << dm.w << ' ' << dm.h << ' ' << dm.refresh_rate << std::endl;

    destRect.x = sourceRect.x = 0;
    destRect.y = sourceRect.y = 0;
    destRect.w = sourceRect.w = 22;
    destRect.h = sourceRect.h;

    for(int i = 0; i < maxW / 22; ++i)
    {
        sourceRect.x = i * 22;
        SDL_RenderCopy(ren, texture, &sourceRect, &destRect);
        SDL_RenderPresent(ren);
        SDL_Delay(500);
        SDL_RenderClear(ren);
    }



    SDL_Quit();
    return 0;
}
