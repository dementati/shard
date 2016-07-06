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

    MOCK_METHOD0(getIntensity, unsigned int());

    MOCK_METHOD1(execute, void(unsigned int));

    MOCK_METHOD0(getJobStack, JobStack&());
};

template<class NeedType>
class MockNeedWrapper : public Need
{
    std::shared_ptr<NeedType> mNeed;

public:
    MockNeedWrapper()
    : 
        mNeed(std::make_shared<NeedType>())
    {
    }

    unsigned int getIntensity() { return mNeed->getIntensity(); }

    void execute(unsigned int dt) { mNeed->execute(dt); }

    NeedType& get()
    {
        return *mNeed;
    }
};
