#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once

using namespace sf;

bool gameOver(int gameGrid[10][20]){
    if (gameGrid[5][1] != 0 || gameGrid[4][1] != 0){
        return 0;
    }
    else
        return 1;
}

