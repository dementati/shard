#pragma once

/**
 * Interface to be implemented by top-level game object.
 */

class Game 
{
public:
    virtual void update(double dt) = 0;

    virtual void render() = 0;
};
