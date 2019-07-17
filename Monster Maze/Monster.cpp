//
//  Monster.cpp
//  Monster Maze
//
//  Created by Robert Schwartz on 7/16/19.
//  Copyright © 2019 Robert Schwartz. All rights reserved.
//

#include <iostream>
#include <thread>
#include <memory>
#include <chrono>
#include <mutex>
#include "Maze.hpp"
#include "Monster.hpp"

Monster::Monster(Maze *maze_ptr, int _row, int _col, char _token) : row(_row), col(_col), token(_token)
{
    std::cout << "DEBUG: Base Monster constructor here" << std::endl;
    monsterThread = std::thread( &Monster::move, this, maze_ptr ,1, 10 ); // WORKS without lambda functions
}

Monster::~Monster()
{
    std::cout << "DEBUG: Monster Destructor here" << std::endl;
    if(monsterThread.joinable())
    {
        monsterThread.join(); //rejoin the thread at destruction time
    }
}

void Monster::printMe()
{
    //DEBUG: print a description of a monster
    std::cout << "Monster " << token << " is at row/col = " << row << "/" << col << std::endl;
}

bool Monster::isAt(int rowRequested, int colRequested)
{
    if(row == rowRequested && col == colRequested) return true;
    else return false;
}

char Monster::getToken()
{
    return token;
}
