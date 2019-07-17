//
//  Ent.cpp
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
#include "Ent.hpp"

Ent::Ent(Maze *maze_ptr, int _row, int _col, char _token) : Monster(maze_ptr, _row, _col, _token)
{
    std::cout << "DEBUG: Ent constructor here" << std::endl;
}

void Ent::move(Maze *maze_ptr, int sleepTime, int hitCount)
{
    while(true)
    {
        maze_ptr->health_mutex.lock();
        if(maze_ptr->gameOver)
        {
            //unlock before leaving, in case health thread stopped the game
            maze_ptr->health_mutex.unlock();
            return;
        }
        if(this->row == maze_ptr->avatarRow && this->col == maze_ptr->avatarCol)
        {
            (maze_ptr->avatarHealth - hitCount) >= 0 ? (maze_ptr->avatarHealth -= hitCount) : (maze_ptr->avatarHealth = 0);
            std::cout << "You were attacked by the Ent! Your health has been decreased to ";
            std::cout << maze_ptr->avatarHealth << std::endl;
        }
        else
        {
            if(this->row < maze_ptr->avatarRow)
            {
                this->row++;
                maze_ptr->printGrid();
            }
            else if(this->row > maze_ptr->avatarRow)
            {
                this->row--;
                maze_ptr->printGrid();
            }
            else if(this->row == maze_ptr->avatarRow && this->col < maze_ptr->avatarCol)
            {
                this->col++;
                maze_ptr->printGrid();
            }
            else if(this->row == maze_ptr->avatarRow && this->col > maze_ptr->avatarCol)
            {
                this->col--;
                maze_ptr->printGrid();
            }
        }
        maze_ptr->health_mutex.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(sleepTime));
    }
}

Ent::~Ent()
{
    std::cout << "DEBUG: Ent Destructor here" << std::endl;
}
