//
//  Maze.cpp
//  Monster Maze
//
//  Created by Robert Schwartz on 7/16/19.
//  Copyright © 2019 Robert Schwartz. All rights reserved.
//

#include <iostream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <math.h>
#include <thread>
#include <chrono>
#include "Maze.hpp"

Maze :: Maze(int newDim, char _avatarToken, char _emptyToken, char _wallToken, char _exitToken) :
             dim(newDim), avatarToken(_avatarToken), emptyToken(_emptyToken), wallToken(_wallToken), exitToken(_exitToken)
{
    avatarRow = newDim/2; //place the avatar at mid-row in the maze
    avatarCol = newDim/2; //place the avatar at mid-row in the maze
    
    gameOver = false;  //initially the game is not over
    avatarHealth = 100; //avatar health starts out at 100 (percent)
    
    for(int i = 0; i < dim; i++)
    {
        //for each row in dim
        //std::cout << "building row " << i << endl;
        
        std::vector<char> row(dim); //create a blank row of dimension (dim)
        grid.push_back(row); //add the row
        
        for(int j = 0; j < dim; j++)
        {
            //for each col in dim
            if(i==0 || i==dim-1)
            {
                grid[i][j] = wallToken; //outer wall
            }
            else if(j==0 || j==dim-1 )
            {
                grid[i][j] = wallToken; //outer wall
            }
            
            else
            {
                grid[i][j] = emptyToken;  //empty
            }
        }
    }
    
    healthThread = std::thread( &Maze::updateHealth, this, 2, 5 );
    
    std::cout << "Note that healthThread.joinable = " << healthThread.joinable() << std::endl;
    
    monster_ptrs.push_back(std::make_shared<Ent>(this, 2, 4)); //adds Ent shared_ptr
    monster_ptrs.push_back(std::make_shared<UrukHai>(this, 4, 2)); //adds Uruk Hai shared_ptr
    
}

Maze::~Maze(){
    //WIP destroy monsters and threads
    std::cout << "~Maze destructing" << std::endl;
    
    if(healthThread.joinable())
    {
        healthThread.join();
    }
    
    monster_ptrs.clear(); //erase the contents of the monster_ptrs vector
}

void Maze::updateHealth(int sleepTime, int healthBoost)
{
    while(true)
    {
        health_mutex.lock(); //wait here until lock is obtained
        
        if(gameOver == true)
        {
            health_mutex.unlock(); //release the lock
            break;
        }
        if(avatarHealth <= 0)
        {
            std::cout << "Your health is gone. Game over!" << std::endl;
            gameOver = true;
            health_mutex.unlock(); //release the lock
            break;
        }
        avatarHealth += healthBoost;
        avatarHealth = (avatarHealth > 100 ? 100 : avatarHealth);
        health_mutex.unlock(); //release the lock
        std::this_thread :: sleep_for( std::chrono::seconds(sleepTime));
    }
    std::cout << "Exiting updateHealth()..." << std::endl;
}

void Maze::printGrid()
{
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[i].size(); j++)
        {
            bool foundMonster = false; //false unless monster is found at this location
            char foundMonsterToken = '?'; //resets when foundMonster == true
            
            for(auto &m : monster_ptrs)
            {
                if(m->isAt(i, j))
                {
                    foundMonster = true;
                    foundMonsterToken = m->getToken();
                }
            }
            
            if(foundMonster)
            {
                std::cout << " " << foundMonsterToken << " "; // print the monster that was found
            }
            
            else if(i==avatarRow && j==avatarCol)
            {
                std::cout << " " << avatarToken << " "; // print the avatar if it is at this location
            }
            else
            {
                std::cout << " " << grid[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
    std:: cout << "Your current health is " << avatarHealth << std::endl;
}

void Maze::takeTurn(std::string direction)
{
    if(direction == Left)
    {
        if(avatarCol > 0 && (grid[avatarRow][avatarCol-1] != wallToken))
        {
            avatarCol--;
            //std::cout << "moving left.\n";
        }
        else
        {
            std::cout << "You hit a wall!" << std::endl;
        }
    }
    else if(direction == Right)
    {
        if(avatarCol < dim-1 && grid[avatarRow][avatarCol+1] != wallToken)
        {
            avatarCol++;
            //std::cout << "moving right.\n";
        }
        else
        {
            std::cout << "You hit a wall!"  << std::endl;
        }
    }
    else if(direction == Up)
    {
        if(avatarRow>0 && grid[avatarRow-1][avatarCol] != wallToken)
        {
            avatarRow--;
            //std::cout << "moving up.\n";
        }
        else
        {
            std::cout << "You hit a wall!"  << std::endl;
        }
    }
    else if(direction == Down)
    {
        if(avatarRow<dim-1 && grid[avatarRow+1][avatarCol] != wallToken)
        {
            avatarRow++;
            //std::cout << "moving down.\n";
        }
        else
        {
            std::cout << "You hit a wall!"  << std::endl;
        }
    }
    if(grid[avatarRow][avatarCol] == exitToken)
    {
        std::cout << "You exited the Maze! (Game Over) \n";
        gameOver = true;
    }
}
