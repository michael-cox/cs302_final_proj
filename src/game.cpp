/*
 * File: game.cpp
 * Michael Cox
 * --------------
 * Instantiates a game object
 * and runs it.
 */

#include "game_object.hpp"

int main(int argc, char** argv)
{
    game g(FULLSCREEN);
    g.runGame();
    return 0;
}
