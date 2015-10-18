#pragma once

#include <iostream>

#include "game.hpp"

class SimpleGame : public Game 
{
public:
    void update(double dt);

    void render();
};
