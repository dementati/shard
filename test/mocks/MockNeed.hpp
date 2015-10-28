#pragma once

#pragma GCC diagnostic ignored "-Weffc++"

#include <gmock/gmock.h>

#include "../../src/logic/Entity.hpp"
#include "../../src/logic/Need.hpp"
#include "../../src/logic/World.hpp"


class MockNeed : public Need
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
    std::shared_ptr<NeedType> mNeed;

public:
    MockNeedWrapper()
        : mNeed(std::make_shared<NeedType>())
    {
    }

    const std::string unitName() const { return mNeed->unitName(); }

    int getIntensity() { return mNeed->getIntensity(); }

    Job& getJob() { return mNeed->getJob(); }

    World& getWorld() { return mNeed->getWorld(); }

    Entity& getOwner() { return mNeed->getOwner(); }

    NeedType& get()
    {
        return *mNeed;
    }
};
