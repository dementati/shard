#pragma once

#include <iostream>

#include "Game.hpp"

// LCOV_EXCL_START
class SimpleGame : public Game 
{
public:
    void update(const double dt);

    void render() const;
};
// LCOV_EXCL_STOP
