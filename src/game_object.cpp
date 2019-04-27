/* The main processing for the game as a whole, this is where
 * majority of the functions are called */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include "game_object.hpp"
#include <random>

#define GAME_NAME "BRB2D"
#define TILE_W 64
#define TILE_H 64
#define RANDOM_CHANCE 500

/* The constructor claims memory for the processors defined that will present and 
 * run the overall game */
game::game(windowMode winMode) : _deadZombies(0), _randGenerator(1), _player(nullptr)
{
    if(winMode == FULLSCREEN) _graphicProc = new graphicProcessor(GAME_NAME);
    else _graphicProc = new graphicProcessor(GAME_NAME, 1024, 576, 0);
    _inputProc = new input;
	_soundProc = new soundProcessor;
    _mainMenu = new menu(_graphicProc, _inputProc, _soundProc);
    _map = new map(_graphicProc->getResolutionW(), _graphicProc->getResolutionH());
    _background = _graphicProc->makeTexture("assets/winter.png", PNG);
    SDL_QueryTexture(_background, NULL, NULL, &_w, &_h);
    enemy::makeCache(_graphicProc);

}

/* Destructor for the game object */
game::~game()
{

    for (std::list<enemy*>::iterator lit = _zombies.begin(); lit != _zombies.end(); ++lit)
    {
        delete *lit;
    }
    _zombies.erase(_zombies.begin(), _zombies.end());
    enemy::clearCache();
    delete _graphicProc;
    delete _inputProc;
    delete _soundProc;
    delete _mainMenu;

}

/* Overall rendering for the main screen of the game */
void game::render()
{
    _graphicProc->clear();
    _graphicProc->renderTextureWithScaling(_background, 0, 0, _w, _h, _graphicProc->getResolutionW(), _graphicProc->getResolutionH(), false);
    for(size_t i = 0; i < _objects.size(); ++i)
    {
        _objects[i]->render();
    }
    _player->render();

    for (std::list<enemy*>::iterator lit = _zombies.begin(); lit != _zombies.end(); ++lit)
    {
        (*lit)->render();
    }
}

/* Controls the switch between the main menu and the main game */
void game::runGame()
{
    for(size_t i = 0; i < _graphicProc->getResolutionW(); i += TILE_W)
        placeWall(i, _graphicProc->getResolutionH() * 4 / 5, CENTER_SNOW);
    for(size_t i = _graphicProc->getResolutionH() * 4 / 5 + TILE_H; i < _graphicProc->getResolutionH(); i += TILE_H)
    {
        for(size_t j = 0; j < _graphicProc->getResolutionW(); j += TILE_W)
        {
            placeWall(j, i, CENTER_DIRT);
        }
    }
    while(1)
    {
        /* Runs the menu until the player starts or exits */
        if(_mainMenu->load() == BUTTON_EXIT) return;
        _soundProc->playSound("gameStart.wav");
        mainLoop();
    }
}

/* Runs the main game */
void game::mainLoop()
{
    /* Delete the player and zombies if the game has been played */
    if(_player != nullptr) delete _player;
    if(_zombies.size() != 0)
    {
        for(std::list<enemy*>::iterator i = _zombies.begin(); i != _zombies.end(); ++i)
            delete (*i);
        _zombies.erase(_zombies.begin(), _zombies.end());
    }
    _deadZombies = 0;

    /* Create a new player, start music */
    SDL_Log("Making new player");
    _player = new player("Player", _graphicProc->getResolutionW() / 2, 20, _graphicProc, _soundProc);
    _soundProc->playSound("gameMusic.wav");
    _player->updateStatus(IDLE);

    while(1)
    {
        /* Renders and checks for sound loops, then processes input, then
         * collision between player, enemies, and projectiles, followed by
         * moving players and enemies */
        render();
        _graphicProc->present();

        if (_soundProc->checkQueue("gameMusic.wav") == 0) { _soundProc->repeat("gameMusic.wav"); }
        switch(_inputProc->readInput())
        {
            case SDLK_SPACE:
                if(_inputProc->readDirection())
                {
                    _player->updateStatus(JUMP);
                }
                break;
            case SDLK_LEFT:
                if(_inputProc->readDirection())
                {
                    _player->updateStatus(MOVING_LEFT);
                } else _player->updateStatus(MOVING_RIGHT);
                break;
            case SDLK_RIGHT:
                if(_inputProc->readDirection())
                {
                    _player->updateStatus(MOVING_RIGHT);
                } else _player->updateStatus(MOVING_LEFT);
                break;
            case SDLK_z:
                if (_inputProc->readDirection()) {
                    _player->updateStatus(ATTACK);
                }
                break;
            case SDLK_ESCAPE:
                if(_inputProc->readDirection()) { _soundProc->stopSound("gameMusic.wav"); return; }
                break;
            default:
                break;
        }

        if (checkCollision((_player->projList))) return;
        _player->move();
        for (std::list<enemy*>::iterator lit = _zombies.begin(); lit != _zombies.end(); lit++)
        {
            (*lit)->seekPlayer(_player->getX());
            (*lit)->move();
        }

        spawnZombies();
    }
}

/* checkCollission - checks for zombie-projectile collisions and player-zombie collissions,
 * acting accordingly */
bool game::checkCollision(std::list<projectile*> & projList) {

    bool deleted = 0;
    std::list<enemy*>::iterator eit;
    std::list<projectile*>::iterator pit;

    /* We check the collision status of every zombie on screen, removing
     * objects in the process if need be */
    for (eit = _zombies.begin(); eit != _zombies.end();) {
        deleted = 0;

        /* Check if a zombie touches a player */
        if ((_player->getY() + _player->getH()) >= (*eit)->getY() + 23) {
            if (((_player->getX() + _player->getW() > (*eit)->getX() + 15) && ((_player->getX() + _player->getW()) < ((*eit)->getX() + (*eit)->getW() - 15))) || ((_player->getX() < ((*eit)->getX() + (*eit)->getW() - 15)) && (_player->getX() > (*eit)->getX() + 15))) { 
                _soundProc->stopSound("gameMusic.wav");
                _soundProc->playSound("playerDamage.wav");
                _soundProc->playSound("enemyAttack.wav");
                SDL_Delay(500);
                _soundProc->playSound("gameWin.wav");
                SDL_Delay(8000);
                return 1;
            }
        }

        /* Then we check if a kunai touches a zombie */
        for (pit = projList.begin(); pit != projList.end(); ) {
            if ((((*pit)->getX() + (*pit)->getW() > (*eit)->getX()) && (((*pit)->getX() + (*pit)->getW()) < ((*eit)->getX() + (*eit)->getW()))) || (((*pit)->getX() < ((*eit)->getX() + (*eit)->getW())) && ((*pit)->getX() > (*eit)->getX()))) { 
                delete (*pit);
                pit = projList.erase(pit);
                _soundProc->playSound("enemyDamage.wav");
                (*eit)->updateHealth();
                if ((*eit)->checkHealth() == 0) {
                    delete (*eit);
                    deleted = 1;
                    eit = _zombies.erase(eit);
                    _soundProc->playSound("enemyDeath.wav");
                    _deadZombies++;
                }
            }
            else { pit++; }
        }
        if (!deleted) { eit++; }
    }
    return 0;
}	

void game::placeWall(int x, int y, wallType type)
{
    wall * newWall;
    switch(type)
    {
        case LEFT_EDGE_SNOW:
            newWall = new wall(x, y, TILE_W, TILE_H, _graphicProc, "assets/wintertileset/png/tiles/1.png", PNG);
            break;
        case CENTER_SNOW:
            newWall = new wall(x, y, TILE_W, TILE_H, _graphicProc, "assets/wintertileset/png/tiles/2.png", PNG);
            break;
        case RIGHT_EDGE_SNOW:
            newWall = new wall(x, y, TILE_W, TILE_H, _graphicProc, "assets/wintertileset/png/tiles/3.png", PNG);
            break;
        case CENTER_DIRT:
            newWall = new wall(x, y, TILE_W, TILE_H, _graphicProc, "assets/wintertileset/png/tiles/5.png", PNG);
            break;
    }

    for(int i = newWall->_y; i < newWall->_y + newWall->_h; ++i)
    {
        for(int j = newWall->_x; j < newWall->_x + newWall->_w; ++j)
        {
            if(i < _map->gameMap.size() && j < _map->gameMap[0].size())
            {
                _map->gameMap[i][j].first = true;
                _map->gameMap[i][j].second.push_back(newWall);
            }
        }
    }

    _objects.push_back(newWall);
}

/* Will continuously spawn zombies based on a chance which increases based on the
 * amount of zombies killed so far */
void game::spawnZombies()
{
    if ((_zombies.size() < maxZombies()) && (_randGenerator() % 100000 <= _deadZombies + RANDOM_CHANCE)) {
        SDL_Log("Spawning zombie");
        bool spawnSide = _randGenerator() % 2;
        enemy * zombie = new enemy("Enemy", spawnSide ? 0 - 200 :_graphicProc->getResolutionW() + 200,  _graphicProc->getResolutionH() * (4 / 5), _graphicProc, _soundProc);
        _zombies.push_back(zombie);
    }
}

/* Used for the spawnZombies function to increase the chance */
int game::maxZombies()
{
    return 4 + (0.25 * _deadZombies); 
}
