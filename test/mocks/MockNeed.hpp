#pragma once

#include <gmock/gmock.h>

#include "../../src/logic/Entity.hpp"
#include "../../src/logic/Need.hpp"
#include "../../src/logic/World.hpp"


class MockNeed : Need
{
public:
    MockNeed() {}

    MOCK_CONST_METHOD0(unitName, const std::string());

    MOCK_METHOD0(getIntensity, int());

    MOCK_METHOD0(getJob, Job&());

    MOCK_METHOD0(getWorld, World&());

    MOCK_METHOD0(getOwner, Entity&());
};

template<class NeedType>
class MockNeedWrapper : public Need
{
    std::shared_ptr<NeedType> wrappedNeed;

public:
    MockNeedWrapper()
        : wrappedNeed(std::make_shared<NeedType>())
    {
    }

    const std::string unitName() const { return wrappedNeed->unitName(); }

    int getIntensity() { return wrappedNeed->getIntensity(); }

    Job& getJob() { return wrappedNeed->getJob(); }

    World& getWorld() { return wrappedNeed->getWorld(); }

    Entity& getOwner() { return wrappedNeed->getOwner(); }

    NeedType& get()
    {
        return *wrappedNeed;
    }
};
