#include <iostream>
#include "map.hpp"

int main()
{
    Map * _map;


    _map = new Map(20, 20);
    char tileType;
    size_t x, y, w, h;
    while(std::cin >> tileType >> w >> h >> x >> y)
    {
        for(size_t i = y; i < y + h; ++i)
        {
            for(size_t j = x; j < x + w; ++j)
            {
                if(i < _map->_width && j < _map->_height)
                    _map->_map[i * _map->_width + j] = tileType;
            }
        }
    }


    for(size_t i = 0; i < _map->_width * _map->_height; ++i)
    {
        if(!(i % _map->_width)) std::cout << std::endl;
        if(_map->_map[i] == 0) std::cout << '-';
        else std::cout << _map->_map[i];
    }
}
