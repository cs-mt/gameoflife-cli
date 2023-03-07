/*
 * Mon 06 Mar 2023 10:35:51 PM UTC
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
#include <ncurses.h>
#include <atomic>

using namespace std::chrono_literals;

std::atomic_bool draw;

void keyLoop(){
    while(true){
        if(!draw){
            int ch = getch();

            if(ch == 100) { // d 
                draw = true;
            }
        }
        std::this_thread::sleep_for(250ms);
    }
}

void gameLoop(){
    std::vector<std::pair<int, int>> startMap;

    startMap.push_back({10,15});
    startMap.push_back({11,15});
    startMap.push_back({12,15});

    Game game;
    MapUtils maputils;

    game.setCurrentMap(startMap);

    while(true){
        if(draw){
            maputils.EnterDrawMode(game);
            draw = false;
        }else {
            std::this_thread::sleep_for(50ms);
            game.nextGeneration();
        }
    }
}

int main(){
    draw = false;

    std::thread t1(gameLoop);
    std::thread t2(keyLoop);

    t2.join();
    t1.join();
}
