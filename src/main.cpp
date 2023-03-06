/*
 *
 * C++ implementation of Conway's Game of Life
 *
 * Author: https://github.com/cs-mt/
 *
 */
#include "game.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "maputils.h"

using namespace std::chrono_literals;

int randomNumber(int start, int end){
    return rand() % end + start;
}

int main(){
    std::vector<std::pair<int, int>> startMap;

    startMap.push_back({10,15});
    startMap.push_back({11,15});
    startMap.push_back({12,15});

    Game game = Game();

    int width,height;

    auto gameSize = game.getGameSize();
    width = gameSize.first;
    height = gameSize.second;

    game.setCurrentMap(startMap);

    MapUtils maputils;
    maputils.EnterDrawMode(game);

    while(true){
        std::this_thread::sleep_for(250ms);
        game.nextGeneration();
    }

}
