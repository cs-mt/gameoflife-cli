/*
 *
 * C++ implementation of Conway's Game of Life
 *
 * Author: https://github.com/cs-mt/
 *
 */

#pragma once

#include <vector>

class Game {
    public:
        Game();
        void nextGeneration();
        void DrawMap(std::vector<std::pair<int, int>> &gameMap);
        std::vector<std::pair<int, int>> getCurrentMap();
        void setCurrentMap(std::vector<std::pair<int, int>> newMap);
        std::pair<int,int> getGameSize();

    private:
        int width,height;
        std::vector<std::pair<int, int>> gameMap;
        bool isAlive(std::vector<std::pair<int, int>> &gameMap, std::pair<int, int> coords);
};
