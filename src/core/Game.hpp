#pragma once

/**
 * Interface to be implemented by top-level game object.
 */

// LCOV_EXCL_START
class Game 
{
public:
    virtual ~Game() {}

    virtual void update(const unsigned int dt) = 0;

    virtual void render() const = 0;
};
// LCOV_EXCL_STOP
