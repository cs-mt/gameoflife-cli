/*
 * Mon 06 Mar 2023 03:06:25 PM UTC
 *
 * C++ implementation of Conway's Game of Life
 *
 * Author: https://github.com/cs-mt/
 *
 */

#include <iostream>
#include <ncurses.h>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std::chrono_literals;

void DrawMap(std::vector<std::pair<int, int>> &gameMap){
    clear();
    for(auto it : gameMap){
        int cellX = it.first;
        int cellY = it.second;

        mvprintw(cellY, cellX, "+");
    }
    refresh();
}

bool isAlive(std::vector<std::pair<int, int>> &gameMap, std::pair<int, int> coords){
    for(auto it : gameMap){
        if (it == coords) return true;
    }
    return false;
}

void calculateNextGen(std::vector<std::pair<int, int>> &gameMap, int width, int height){
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
        // If dead, needs to have exactly 3 neighbors to keep living.

        if(isAlive(gameMap, {neighborX, neighborY})){
            if(neighborCount == 2 || neighborCount == 3){
                newMap.push_back({neighborX, neighborY});              
            }
        }else if(neighborCount == 3){
            newMap.push_back({neighborX, neighborY});
        }
    }

    gameMap = newMap;
}

int randomNumber(int start, int end){
    return rand() % end + start;
}

int main(){
    int height, width;
    initscr();
    getmaxyx(stdscr, height, width);

    srand(15);

    std::vector<std::pair<int,int>> gameMap;

    for(int i=0;i<1000;i++){
        int randX = randomNumber(0, width);
        int randY = randomNumber(0, height);

        gameMap.push_back({randX, randY});
    }

    /*
    // Block
    gameMap.push_back({10,10});
    gameMap.push_back({10,11});
    gameMap.push_back({11,10});
    gameMap.push_back({11,11});

    // Blinker
    gameMap.push_back({10,15});
    gameMap.push_back({11,15});
    gameMap.push_back({12,15});

    // Glider
    gameMap.insert(gameMap.end(), {{8, 21}, {9, 22} ,{10, 20}, {10, 21}, {10, 22}});
    */

    while(true){
        std::this_thread::sleep_for(10ms);
        DrawMap(gameMap);
        calculateNextGen(gameMap, width, height);
    }
}
