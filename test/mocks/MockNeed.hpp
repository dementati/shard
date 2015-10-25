#pragma once

#include <gmock/gmock.h>

#include "../../src/logic/Entity.hpp"
#include "../../src/logic/Need.hpp"
#include "../../src/logic/World.hpp"

class MockNeed : public Need
{
public:
    MOCK_CONST_METHOD0(unitName, const std::string());

    MOCK_METHOD0(getIntensity, int());

    MOCK_METHOD0(getJob, Job&());

    MOCK_METHOD0(getWorld, World&());

    MOCK_METHOD0(getOwner, Entity&());
};
