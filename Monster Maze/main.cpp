//
//  main.cpp
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
#include "Maze.hpp"

int main(int argc, const char * argv[])
{
    std::cout << "Maze Test\n";
    
    Maze myMaze(15);
    myMaze.printGrid();
    std::string word; // the string input by the player to indicate up, down, left, right
    
    std::cout << "Let's play...\n";
    
    std::cout << "\nWhat direction would you like to move: ";
    std::cout << myMaze.Left << ", " << myMaze.Right << ", " << myMaze.Up << ", " << myMaze.Down << "? ";
    
    while(!myMaze.gameOver)
    {
        std::cin >> word;
        myMaze.takeTurn(word);
        myMaze.printGrid();
    }
    
    std::cout << "Goodbye!" << std::endl;
    
    return 0;
}
