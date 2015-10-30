#pragma once

// LCOV_EXCL_START
class Renderable
{
public:
    virtual ~Renderable() {}

    virtual void draw() = 0;
};
// LCOV_EXCL_STOP
