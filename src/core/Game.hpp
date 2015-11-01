#pragma once

/**
 * Interface to be implemented by top-level game object.
 */

class Game 
{
public:
    // LCOV_EXCL_START
    virtual ~Game() {}
    // LCOV_EXCL_STOP

    virtual void update(const unsigned int dt) = 0;

    virtual void render() const = 0;
};
