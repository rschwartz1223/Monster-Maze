//
//  Monster.hpp
//  Monster Maze
//
//  Created by Robert Schwartz on 7/16/19.
//  Copyright © 2019 Robert Schwartz. All rights reserved.
//

#ifndef MONSTER_HPP
#define MONSTER_HPP
#include <thread>
#include <memory>
#include <chrono>
#include <mutex>
#include "Maze.hpp"

class Maze;

class Monster
{
protected:
    int row;  //row position of our Monster from zero to dim-1
    int col; //column position of our Monster from zero to dim-1
    char token; //character that represents this Monster
    std::thread monsterThread; //instance of thread that manages the Monster
    
public:
    //constructor
    Monster(Maze *maze_ptr, int _row=0, int _col=0, char _token='M');
    //destructor
    ~Monster();

    virtual void move(Maze *maze_ptr, int sleepTime, int hitCount ) = 0;
    void printMe(); //DEBUG
    bool isAt(int row, int col); //true if this monster is at a requested row/col location
    char getToken(); //return the token for this Monster
};

#endif
