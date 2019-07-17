//
//  Maze.hpp
//  Monster Maze
//
//  Created by Robert Schwartz on 7/16/19.
//  Copyright © 2019 Robert Schwartz. All rights reserved.
//

#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <thread>
#include <memory>
#include <mutex>
#include "Monster.hpp"
#include "Ent.hpp"
#include "UrukHai.hpp"

class Maze
{
private:
    char avatarToken; //character that represents the avatar
    char emptyToken; //character that represents empty space in the maze
    char wallToken; //character that represents a wall
    char exitToken; //character that represents an exit - where you quit the game
    
    std::vector< std::vector<char> > grid;
    std::vector< std::shared_ptr<Monster> > monster_ptrs; //vector of shared monster pointers
    
public:
    int dim; //width of this square maze
    int avatarRow; //row position of our avatar from zero to dim-1
    int avatarCol; //column position of our avatar from zero to dim-1
    int avatarHealth; //value from 0 to 100 that represents the current health of the avatar

    const std::string Up = "w";
    const std::string Down = "s";
    const std::string Left = "a";
    const std::string Right = "d";
    
    std::mutex health_mutex; //indicates ability to lock to prevent thead corruption.
    std::thread healthThread; //instance of thread that manages the boss
    
    bool gameOver; //initialized to false in constructor and set to true either by takeTurn or by moveBoss
    
    //constructor
    Maze(int newDim = 4, char _avatarToken = 'A', char _emptyToken = ' ', char _wallToken = '*', char _exitToken = 'E');
    //destructor
    ~Maze();
    
    void printGrid();
    void takeTurn(std::string direction); //move the avatar in the requested direction if possible
    void updateHealth( int sleepTime, int healthBoost ); //increases health by healthBoost each time sleepTime microseconds
};

#endif
