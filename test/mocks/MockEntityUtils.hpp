#pragma once

#include <gmock/gmock.h>

#include "../../src/logic/utility/EntityUtils.hpp"

class MockEntityUtils : public EntityUtils
{
public:
    MOCK_METHOD2(updateStepTimer, void(Entity&, unsigned int));

    MOCK_METHOD1(canMove, bool(Entity&));

    MOCK_METHOD2(move, void(Entity&, glm::ivec2));
};
