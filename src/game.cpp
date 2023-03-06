/*
 * Mon 06 Mar 2023 10:35:51 PM UTC
 *
 * C++ implementation of Conway's Game of Life
 *
 * Author: https://github.com/cs-mt/
 *
 */

#include "game.h"
#include <ncurses.h>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <algorithm>

Game::Game(){
    initscr();
    getmaxyx(stdscr, height, width);
}

bool Game::isAlive(std::vector<std::pair<int, int>> &gameMap, std::pair<int, int> coords){
    for(auto it : gameMap){
        if (it == coords) return true;
    }
    return false;
}

void Game::nextGeneration(){
    std::map<std::pair<int,int>, int> neighbors;

    for(auto it : gameMap){
        int cellX = it.first;
        int cellY = it.second;

        // Neighbor coordinates:
        // [x-1, y-1], [x, y-1], [x+1, y-1]
        // [x-1, y], CURRENTCELL, [x+1, y]
        // [x-1, y+1], [x, y+1], [x+1, y+1]

        ++neighbors[{cellX-1, cellY-1}];
        ++neighbors[{cellX, cellY-1}];
        ++neighbors[{cellX+1, cellY-1}];

        ++neighbors[{cellX-1, cellY}];
        ++neighbors[{cellX+1, cellY}];

        ++neighbors[{cellX-1, cellY+1}];
        ++neighbors[{cellX, cellY+1}];
        ++neighbors[{cellX+1, cellY+1}];
    }

    std::vector<std::pair<int, int>> newMap;

    for(const auto &neighbor : neighbors){
        int neighborX = neighbor.first.first;
        int neighborY = neighbor.first.second;

        if(neighborX > width+10 || neighborY > height+10 || neighborX < -10 || neighborY < -10){
            continue;
        }

        int neighborCount = neighbor.second;

        // If alive, needs to have 2 or 3 live neighbors to keep living.
        // If dead, needs to have exactly 3 neighbors to get revived.

        if(isAlive(gameMap, {neighborX, neighborY})){
            if(neighborCount == 2 || neighborCount == 3){
                newMap.push_back({neighborX, neighborY});              
            }
        }else if(neighborCount == 3){
            newMap.push_back({neighborX, neighborY});
        }
    }

    gameMap = newMap;

    DrawMap(gameMap);
}


void Game::DrawMap(std::vector<std::pair<int, int>> &gameMap){
    clear();
    for(auto it : gameMap){
        int cellX = it.first;
        int cellY = it.second;

        mvprintw(cellY, cellX, "#");
    }
    refresh();
}

std::pair<int,int> Game::getGameSize(){
    return {width, height};
}

void Game::setCurrentMap(std::vector<std::pair<int, int>> newMap){
    gameMap = newMap;
}

std::vector<std::pair<int, int>> Game::getCurrentMap(){
    return gameMap;
}
