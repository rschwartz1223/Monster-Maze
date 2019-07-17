//
//  UrukHai.cpp
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
#include "UrukHai.hpp"


UrukHai::UrukHai(Maze *maze_ptr, int _row, int _col, char _token) : Monster(maze_ptr, _row, _col, _token)
{
    std::cout << "DEBUG: Uruk Hai constructor here" << std::endl;
}

void UrukHai::move(Maze *maze_ptr, int sleepTime, int hitCount)
{
    while(true)
    {
        maze_ptr->health_mutex.lock();
        if(maze_ptr->gameOver)
        {
            maze_ptr->health_mutex.unlock(); //unlock before we leave, incase health thread stopped the game
            return;
        }
        if(this->row == maze_ptr->avatarRow && this->col == maze_ptr->avatarCol)
        {
            (maze_ptr->avatarHealth - hitCount) >= 0 ? (maze_ptr->avatarHealth -= hitCount) : (maze_ptr->avatarHealth = 0);
            std::cout << "You were attacked by the Uruk Hai! Your health has been decreased to ";
            std::cout << maze_ptr->avatarHealth << std::endl;
        }
        else
        {
            //if avatar is down-right of uruk hai
            if(this->row < maze_ptr->avatarRow && this->col < maze_ptr->avatarCol)
            {
                this->row++;
                this->col++;
                maze_ptr->printGrid();
            }
            //if avatar is down-left of uruk hai
            else if(this->row < maze_ptr->avatarRow && this->col > maze_ptr->avatarCol)
            {
                this->row++;
                this->col--;
                maze_ptr->printGrid();
            }
            //if avatar is up-right of uruk hai
            else if(this->row > maze_ptr->avatarRow && this->col < maze_ptr->avatarCol)
            {
                this->row--;
                this->col++;
                maze_ptr->printGrid();
            }
            //if avatar is up-left of uruk hai
            else if(this->row > maze_ptr->avatarRow && this->col > maze_ptr->avatarCol)
            {
                this->row--;
                this->col--;
                maze_ptr->printGrid();
            }
            //if avatar is right of uruk hai
            else if(this->row == maze_ptr->avatarRow && this->col < maze_ptr->avatarCol)
            {
                this->col++;
                maze_ptr->printGrid();
            }
            //if avatar is left of uruk hai
            else if(this->row == maze_ptr->avatarRow && this->col > maze_ptr->avatarCol)
            {
                this->col--;
                maze_ptr->printGrid();
            }
            //if avatar is below uruk hai
            else if(this->col == maze_ptr->avatarCol && this->row > maze_ptr->avatarRow)
            {
                this->row--;
                maze_ptr->printGrid();
            }
            //if avatar is above uruk hai
            else if(this->col == maze_ptr->avatarCol && this->row < maze_ptr->avatarRow)
            {
                this->row++;
                maze_ptr->printGrid();
            }
        }
        maze_ptr->health_mutex.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(sleepTime));
    }
}

UrukHai::~UrukHai()
{
    std::cout << "DEBUG: Uruk Hai Destructor here" << std::endl;
}
