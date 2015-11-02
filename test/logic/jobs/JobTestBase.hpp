#pragma once

#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../mocks/MockEntity.hpp"
#include "../../mocks/MockGameObject.hpp"
#include "../../mocks/MockRNG.hpp"
#include "../../mocks/MockWorld.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 
using ::testing::StrEq; 
using ::testing::Ref; 
using ::testing::_; 

using MockEntityType = ::testing::NiceMock<MockEntity>;
using MockGameObjectType = ::testing::NiceMock<MockGameObject>;
using MockWorldType = ::testing::NiceMock<MockWorld>;
using MockRNGType = ::testing::NiceMock<MockRNG>;

class JobTestBase : public ::testing::Test
{
protected:
    MockWorldType mWorld;
    MockEntityType mOwner;
    MockGameObjectType mWater;
    MockRNGType mRng;

    Variant mOwnerPosition;
    Variant mOwnerPerception;
    glm::ivec2 mDefaultTarget;
    Variant mOwnerTimeSinceLastStep;
    Variant mOwnerSpeed;
    Variant mOwnerThirst;

    Variant mWaterThirstReduction;
    Variant mWaterPosition;

    JobTestBase()
    :
        mOwnerPosition(glm::ivec2(0, 0)),
        mOwnerPerception((unsigned int)1),
        mDefaultTarget(glm::ivec2(0, 1)),
        mOwnerTimeSinceLastStep((unsigned int)0),
        mOwnerSpeed(1.0f),
        mOwnerThirst((unsigned int)0),
        mWaterThirstReduction((unsigned int)0),
        mWaterPosition(glm::ivec2(0, 0))
    {
        ON_CALL(mOwner, hasAttribute(StrEq("perception")))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute(StrEq("perception")))
            .WillByDefault(ReturnRef(mOwnerPerception));
        ON_CALL(mOwner, hasAttribute(StrEq("position")))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute(StrEq("position")))
            .WillByDefault(ReturnRef(mOwnerPosition));
        ON_CALL(mOwner, hasAttribute(StrEq("timeSinceLastStep")))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute(StrEq("timeSinceLastStep")))
            .WillByDefault(ReturnRef(mOwnerTimeSinceLastStep));
        ON_CALL(mOwner, hasAttribute(StrEq("speed")))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute(StrEq("speed")))
            .WillByDefault(ReturnRef(mOwnerSpeed));
        ON_CALL(mOwner, hasAttribute(StrEq("thirst")))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute(StrEq("thirst")))
            .WillByDefault(ReturnRef(mOwnerThirst));

        ON_CALL(mWater, hasAttribute(StrEq("thirstReduction")))
            .WillByDefault(Return(true));
        ON_CALL(mWater, getAttribute(StrEq("thirstReduction")))
            .WillByDefault(ReturnRef(mWaterThirstReduction));
        ON_CALL(mWater, hasAttribute(StrEq("position")))
            .WillByDefault(Return(true));
        ON_CALL(mWater, getAttribute(StrEq("position")))
            .WillByDefault(ReturnRef(mWaterPosition));
    }

    void setOwnerSpeed(float speed)
    {
        mOwnerSpeed.set<float>(speed);
    }

    void setOwnerPerception(unsigned int perception)
    {
        mOwnerPerception.set<unsigned int>(perception);
    }

    void setOwnerThirst(unsigned int thirst)
    {
        mOwnerThirst.set<unsigned int>(thirst);
    }

    void setWaterThirstReduction(unsigned int reduction)
    {
        mWaterThirstReduction.set<unsigned int>(reduction);
    }

    void setOwnerPosition(glm::ivec2 position)
    {
        mOwnerPosition.set<glm::ivec2>(position);
    }

    void setWaterPosition(glm::ivec2 position)
    {
        mWaterPosition.set<glm::ivec2>(position);
    }

    void setWaterConsumable(bool consumable)
    {
        ON_CALL(mWater, hasAttribute(StrEq("consumable")))
            .WillByDefault(Return(consumable));
    }
};
