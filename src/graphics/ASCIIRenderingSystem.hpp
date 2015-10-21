#pragma once

#include <vector>

#include "../core/object.hpp"
#include "CharBitmap.hpp"

// LCOV_EXCL_START
class ASCIIRenderingSystem : public Object
{
public:
    virtual void drawBitmap(const CharBitmap &bitmap, const int x, const int y) = 0;
};
// LCOV_EXCL_STOP
