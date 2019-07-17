//
//  Ent.hpp
//  Monster Maze
//
//  Created by Robert Schwartz on 7/16/19.
//  Copyright © 2019 Robert Schwartz. All rights reserved.
//

#ifndef ENT_HPP
#define ENT_HPP

#include <thread>
#include "Maze.hpp"
#include "Monster.hpp"

class Ent : public Monster
{
public:
    
    std::thread entThread;
    
    //constructor for Ent
    Ent(Maze *maze_ptr, int _row=0, int _col=0, char _token='E');
    
    //Destructor for Ent
    ~Ent();
    
    //overridden move method from Monster base class
    void move(Maze *maze_ptr, int sleepTime, int hitCount);
};

#endif
