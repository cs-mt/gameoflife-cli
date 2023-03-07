#include "maputils.h"
#include <curses.h>
#include <ncurses.h>
#include <fstream>
#include <chrono>
#include <string>
#include <iterator>
#include <iostream>

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

void MapUtils::RandomizeMap(std::vector<std::pair<int, int>> &gameMap, int width, int height){
    gameMap = {};

    srand(clock());

    for(int i=0;i<width*height/6;i++){
        int randX = rand() % width + 0;
        int randY = rand() % height + 0;

        gameMap.push_back({randX, randY});
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
            game.setCurrentMap(gameMap);
            std::string mapName;

            mvprintw(0, 0, "Enter a name for map: ");

            int ch2 = getch();

            while( ch2 != '\n' ){
                mapName.push_back(ch2);
                ch2 = getch();
            }

            SaveMap(gameMap, mapName);
            break;
        }else if(ch == 32){ // space
            TogglePoint(gameMap, selectionX, selectionY);
        }else if(ch == 108) {// l
            std::string mapName;

            mvprintw(0, 0, "Name of the map to load: ");

            int ch2 = getch();

            while( ch2 != '\n' ){
                mapName.push_back(ch2);
                ch2 = getch();
            }

            auto loadedMap = LoadMap(mapName);
            game.setCurrentMap(loadedMap);
            break;
        }else if(ch == 114) { // r
            RandomizeMap(gameMap, width, height);
        }
    }
}

void MapUtils::SaveMap(std::vector<std::pair<int, int>> &gameMap, std::string mapName){
    std::ofstream file("Maps/" + mapName + ".map", std::ios::trunc);

    if(file.is_open()){
        for(auto it : gameMap){

            int x = it.first;
            int y = it.second;

            file << x << "," << y << "-";
        }
        file.close();
    }
}

std::vector<std::pair<int, int>> MapUtils::LoadMap(std::string mapName){
    std::ifstream file("Maps/" + mapName + ".map");
    std::string mapStr;
    getline(file, mapStr);

    std::vector<std::pair<int, int>> loadedMap;

    std::string part;
    int x=-1,y=-1;

    for( auto it : mapStr ){
        if(it == ','){
            x = stoi(part);
            part = "";
            continue;
        }else if(it == '-'){
            y = stoi(part);
            part = "";
            loadedMap.push_back({x,y});
            x=-1;
            y=-1;
            continue;
        }
        part += it;
    }

    return loadedMap;
}
