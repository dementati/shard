#pragma once

#include <gmock/gmock.h>

#include "../../src/logic/World.hpp"

class MockWorld : public World
{
public:
    MOCK_METHOD0(getEntities, std::vector<Entity>&());

    MOCK_METHOD1(add, void(Entity entity));
};
