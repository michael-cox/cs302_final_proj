#include "window_object.hpp"

int main(int argc, char** argv)
{
    GWin game("Test game");
    game.runGame();
    SDL_Quit();
    return 0;
}
