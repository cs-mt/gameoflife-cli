/* 
 * Mon 06 Mar 2023 10:35:51 PM UTC
 *
 * C++ implementation of Conway's Game of Life
 *
 * Author: https://github.com/cs-mt/
 *
 */

#pragma once

#include <vector>
#include "game.h"
#include <string>

class MapUtils {
    public:
        void EnterDrawMode(Game &game);
        void TogglePoint(std::vector<std::pair<int, int>> &gameMap, int selectionX, int selectionY);
        void SaveMap(std::vector<std::pair<int, int>> &gameMap, std::string mapName);
        std::vector<std::pair<int, int>> LoadMap(std::string mapName);
        void RandomizeMap(std::vector<std::pair<int, int>> &gameMap, int width, int height);
};



