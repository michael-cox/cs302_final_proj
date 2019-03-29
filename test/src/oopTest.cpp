#include "window_object.hpp"

int main(int argc, char **argv)
{

    GWin game("New Game");

    game.runGame();

    SDL_Quit();

    return 0;
}
