#pragma once

#include <iostream>

#include "game.hpp"

class SimpleGame : public Game 
{
public:
    void update(const double dt);

    void render() const;
};
