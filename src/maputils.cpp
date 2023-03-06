/*
 *
 * C++ implementation of Conway's Game of Life
 *
 * Author: https://github.com/cs-mt/
 *
 */

#include "maputils.h"
#include <ncurses.h>
#include <fstream>
#include <chrono>
#include <string>
#include <iterator>

void MapUtils::TogglePoint(std::vector<std::pair<int, int>> &gameMap, int selectionX, int selectionY){
    auto exists = -1;
    for(int i=0;i<gameMap.size();i++){
        if(gameMap[i] == std::make_pair(selectionX, selectionY)){
            exists = i;
        }
    }
    if(exists == -1){
        gameMap.push_back({selectionX, selectionY});                
    }else {
        gameMap.erase(gameMap.begin() + exists);
    }
}

void MapUtils::EnterDrawMode(Game &game){
    int selectionX=0, selectionY=0;

    std::vector<std::pair<int, int>> gameMap = game.getCurrentMap();

    auto windowSize = game.getGameSize();
    int width = windowSize.first;
    int height = windowSize.second;

    while(true){
        game.DrawMap(gameMap);

        if(selectionX < 0) selectionX = 0;
        if(selectionY < 0) selectionY = 0;
        if(selectionX > width) selectionX = width;
        if(selectionY > height) selectionY = height;

        wmove(stdscr, selectionY, selectionX);

        char ch = getch();

        if(ch == 119){ // w
            --selectionY;
        }else if(ch == 115){ // s
            ++selectionY;
        }else if(ch == 97){ // a
            --selectionX;
        }else if(ch == 100){ // d
            ++selectionX;
        }else if(ch == 101){ // e
            game.setCurrentMap(gameMap);
            break;
        }else if(ch == 103){ // g
            SaveMap(gameMap);
            break;
        }else if(ch == 32){ // space
            TogglePoint(gameMap, selectionX, selectionY);
        }
    }
}

void MapUtils::SaveMap(std::vector<std::pair<int, int>> &gameMap){
    const auto timeNow = std::chrono::system_clock::now();
    int timeNowUnix = std::chrono::duration_cast<std::chrono::seconds>(timeNow.time_since_epoch()).count();

    std::ofstream file("Maps/" + std::to_string(timeNowUnix) + ".map");

    if(file.is_open()){
        for(auto it : gameMap){

            int x = it.first;
            int y = it.second;

            file << x << "," << y << "-";
        }
        file.close();
    }
}
