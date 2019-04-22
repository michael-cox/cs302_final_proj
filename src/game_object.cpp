#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include <fstream>
#include "menu.hpp"
#include "game_object.hpp"
#include "map.hpp"
#include "character.hpp"

bool GWin::_isInit = 0;

size_t GWin::_numInst = 0;

GWin::GWin(std::string windowTitle) : _win(nullptr), _ren(nullptr), _map(nullptr),
    _display(nullptr)
{
    SDL_Log("Constructing GWin...");
    initSDL();
    createWindow(windowTitle);
    if(SDL_SetHintWithPriority(SDL_HINT_RENDER_SCALE_QUALITY, "0", SDL_HINT_OVERRIDE)) SDL_Log("Hint set properly!");
    SDL_Log("Finished constructing GWin");
    keyInput = new input;
}

GWin::GWin(std::string windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags) : _win(nullptr), _ren(nullptr),
    _map(nullptr), _display(nullptr)
{
    SDL_Log("Constructing GWin...");
    initSDL();
    createWindow(windowTitle, windowWidth, windowHeight, windowFlags);
    if(SDL_SetHintWithPriority(SDL_HINT_RENDER_SCALE_QUALITY, "0", SDL_HINT_OVERRIDE)) SDL_Log("Hint set properly!");
    SDL_Log("Finished constructing GWin");
    keyInput = new input;
    _display->w = windowWidth;
    _display->h = windowHeight;
}

GWin::~GWin()
{
    SDL_DestroyWindow(_win);
    SDL_DestroyRenderer(_ren);
    if(_map != nullptr) delete _map;
    --_numInst;
    SDL_Log("_numInst (after destructing): %zu", _numInst);
    delete _display;
    delete imgProc;
    delete keyInput;
    if(!_numInst) { SDL_Log("Quitting SDL..."); SDL_Quit(); }
}

void GWin::initSDL()
{
    if(!_isInit)
    {
        SDL_Log("Initializing SDL...");
        if(SDL_Init(SDL_INIT_EVERYTHING))
            SDL_Log("Failed to initialize SDL. Error: %s", SDL_GetError());
        getDisplayMode();
        _isInit = 1;
        SDL_Log("Finished initializing SDL");
    }
    ++_numInst;
    SDL_Log("_numInst (after constructing): %zu", _numInst);
}

void GWin::getDisplayMode()
{
    SDL_Log("Getting display mode...");
    if(_display == nullptr) _display = new SDL_DisplayMode;
    if(SDL_GetCurrentDisplayMode(0, _display))
    {
        SDL_Log("Failed to get display mode. Error: %s", SDL_GetError());
    }
    SDL_Log("Display mode: %dx%d %d Hz", _display->w, _display->h, _display->refresh_rate);
}

void GWin::createWindow(std::string windowTitle)
{
    SDL_Log("Creating window...");
    _win = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            _display->w, _display->h, SDL_WINDOW_FULLSCREEN);
    assert(_win != nullptr);
    _ren = SDL_CreateRenderer(_win, -1, SDL_RENDERER_PRESENTVSYNC);
    assert(_ren != nullptr);
    imgProc = new imageProcessor(_ren);
    _background = imgProc->makeTexture("assets/winter.png", png);
    imgProc->renderTexture(_background, 0, 0, _display->w, _display->h);
    imgProc->present();
    SDL_Log("Finished creating window.");
}

void GWin::createWindow(std::string windowTitle, int windowWidth, int windowHeight, uint32_t windowFlags)
{
    SDL_Log("Creating window...");
    _win = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            windowWidth, windowHeight, windowFlags);
    assert(_win != nullptr);
    _ren = SDL_CreateRenderer(_win, -1, SDL_RENDERER_PRESENTVSYNC);
    assert(_ren != nullptr);
    imgProc = new imageProcessor(_ren);
    _background = imgProc->makeTexture("assets/winter.png", png);
    imgProc->renderTexture(_background, 0, 0, _display->w, _display->h);
    imgProc->present();
    SDL_Log("Finished creating window.");
}

void GWin::render()
{
    SDL_RenderClear(_ren);
    imgProc->renderTexture(_background, 0, 0, _display->w, _display->h);
}

void GWin::loadMapFromText(std::string filename)
{
    std::ifstream mapStream;
    if(_map != nullptr)
    {
        SDL_Log("Map already exists... deleting...");
        delete _map;
    }
    SDL_Log("Constructing map...");
    _map = new Map(_display->w, _display->h);
    SDL_Log("Constructed map.");
    mapStream.open(filename);
    if(mapStream.fail())
    {
        SDL_Log("Failed to open file %s.", filename.c_str());
    }
    char tileType;
    size_t x, y, w, h;
    while(mapStream >> tileType >> w >> h >> x >> y)
    {
        SDL_Log("%c %zu %zu %zu %zu", tileType, w, h, x, y);
        for(size_t i = y; i < y + h; ++i)
        {
            for(size_t j = x; j < x + w; ++j)
            {
                if(i < _map->_width && j < _map->_height)
                    _map->_map[i * _map->_width + j] = tileType;
            }
        }
    }
}

void GWin::dumpMap()
{
    std::string output;
    for(size_t i = 0; i < _map->_width * _map->_height; ++i)
    {
        if(!(i % _map->_width))
        {
            SDL_Log("%s", output.c_str());
            output = "";
        }
        if(_map->_map[i] == 0) output += '-';
        else output += _map->_map[i];
    }
    SDL_Log("%s", output.c_str());
}

void GWin::runGame()
{
    loadMainMenu();

    player p("Player", 15, 20, imgProc);

    SDL_Delay(500);
    SDL_Keycode key;
    while(1)
    {
        render();
        p.render();
        imgProc->present();
        key = keyInput->readInput();
        switch(key)
        {
            case SDLK_UP:
                if(keyInput->readDirection())
                {
                    p.updateStatus(MOVING_UP);
                } else p.updateStatus(STILL);
                break;
            case SDLK_DOWN:
                if(keyInput->readDirection())
                {
                    p.updateStatus(MOVING_DOWN);
                } else p.updateStatus(STILL);
                break;
            case SDLK_LEFT:
                if(keyInput->readDirection())
                {
                    p.updateStatus(MOVING_LEFT);
                } else p.updateStatus(STILL);
                break;
            case SDLK_RIGHT:
                if(keyInput->readDirection())
                {
                    p.updateStatus(MOVING_RIGHT);
                } else p.updateStatus(STILL);
                break;
            case SDLK_RETURN:
                if(keyInput->readDirection())
                {
                    SDL_Log("Got return");
                    return;
                }
                break;
            default:
                p.move();
                break;
        }
    }
}

void GWin::loadMainMenu()
{
    menu mainMenu(imgProc, keyInput, _display);
    if(mainMenu.menuLoop() == BUTTON_EXIT) return;
}
