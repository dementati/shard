#pragma once

/**
 * Interface to be implemented by top-level game object.
 */

class Game 
{
public:
    virtual void update(const double dt) = 0;

    virtual void render() const = 0;
};
