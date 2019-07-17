//
//  UrukHai.hpp
//  Monster Maze
//
//  Created by Robert Schwartz on 7/16/19.
//  Copyright © 2019 Robert Schwartz. All rights reserved.
//

#ifndef URUKHAI_HPP
#define URUKHAI_HPP

#include <thread>
#include "Maze.hpp"
#include "Monster.hpp"

class UrukHai : public Monster
{
public:
    
    std::thread urukHaiThread;
    
    //constructor
    UrukHai(Maze *maze_ptr, int _row=0, int _col=0, char _token='U');
    //destructor
    ~UrukHai();
    
    //overridden move method from Monster base class
    void move(Maze *maze_ptr, int sleepTime, int hitCount);
};

#endif
