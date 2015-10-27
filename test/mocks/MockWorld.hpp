#pragma once

#include <gmock/gmock.h>

#include "../../src/logic/World.hpp"

class MockWorld : public World
{
public:
    MOCK_METHOD0(getEntities, std::vector<std::unique_ptr<Entity>>&());

    virtual void add(std::unique_ptr<Entity> entity)
    {
        addProxy(entity.get());
    }
    MOCK_METHOD1(addProxy, void(Entity*));
};
