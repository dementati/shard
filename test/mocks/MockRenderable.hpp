#pragma once

#pragma GCC diagnostic ignored "-Weffc++"

#include <gmock/gmock.h>

#include "../../src/graphics/Renderable.hpp"

class MockRenderable : public Renderable
{
public:
    MOCK_METHOD0(draw, void());

    MOCK_METHOD0(getId, int());

    MOCK_CONST_METHOD0(unitName, const std::string());
};

