#pragma once

#include <gmock/gmock.h>

#include "../../src/logic/Entity.hpp"

class MockEntity : public Entity
{
public:
    MockEntity(const std::string renderableId)
        : Entity(renderableId) {}

    virtual void addNeed(std::unique_ptr<Need> need)
    {
        addNeedProxy(need.get());
    }
    MOCK_METHOD1(addNeedProxy, void(Need*));

    MOCK_METHOD0(selectNeed, Need&());

    MOCK_METHOD0(getPosition, glm::ivec2());

    MOCK_METHOD1(setPosition, void(glm::ivec2));

    MOCK_METHOD0(getRenderableId, const std::string());

    MOCK_CONST_METHOD0(unitName, const std::string());
};
