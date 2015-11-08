#pragma once

#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../mocks/MockEntity.hpp"
#include "../mocks/MockGameObject.hpp"
#include "../mocks/MockRNG.hpp"
#include "../mocks/MockWorld.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 
using ::testing::StrEq; 
using ::testing::Ref; 
using ::testing::_; 

using MockGameObjectType = ::testing::NiceMock<MockGameObject>;
using MockEntityType = ::testing::NiceMock<MockEntity>;
using MockWorldType = ::testing::NiceMock<MockWorld>;
using MockRNGType = ::testing::NiceMock<MockRNG>;

class LogicTestBase : public ::testing::Test
{
protected:
    MockWorldType mWorld;
    Variant mWorldRunning;
    Variant mWorldCameraPosition;

    MockEntityType mOwner;
    Variant mOwnerPosition;
    Variant mOwnerPerception;
    glm::ivec2 mDefaultTarget;
    Variant mOwnerTimeSinceLastStep;
    Variant mOwnerSpeed;
    Variant mOwnerThirst;
    Variant mOwnerMaxThirst;

    MockGameObjectType mWater;
    Variant mWaterThirstReduction;
    Variant mWaterPosition;

    MockRNGType mRng;

    LogicTestBase()
    :
        mWorldRunning(true),
        mWorldCameraPosition(glm::ivec2(0, 0)),

        mOwnerPosition(glm::ivec2(0, 0)),
        mOwnerPerception((unsigned int)1),
        mDefaultTarget(glm::ivec2(0, 1)),
        mOwnerTimeSinceLastStep((unsigned int)0),
        mOwnerSpeed(1.0f),
        mOwnerThirst((unsigned int)0),
        mOwnerMaxThirst((unsigned int)0),

        mWaterThirstReduction((unsigned int)0),
        mWaterPosition(glm::ivec2(0, 0))
    {
        ON_CALL(mWorld, hasAttribute(StrEq("running")))
            .WillByDefault(Return(true));
        ON_CALL(mWorld, getAttribute(StrEq("running")))
            .WillByDefault(ReturnRef(mWorldRunning));
        ON_CALL(mWorld, hasAttribute(StrEq("cameraPosition")))
            .WillByDefault(Return(true));
        ON_CALL(mWorld, getAttribute(StrEq("cameraPosition")))
            .WillByDefault(ReturnRef(mWorldCameraPosition));
        ON_CALL(mWorld, isBlocked(_))
            .WillByDefault(Return(false));

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
        ON_CALL(mOwner, hasAttribute(StrEq("maxThirst")))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute(StrEq("maxThirst")))
            .WillByDefault(ReturnRef(mOwnerMaxThirst));

        ON_CALL(mWater, hasAttribute(StrEq("thirstReduction")))
            .WillByDefault(Return(true));
        ON_CALL(mWater, getAttribute(StrEq("thirstReduction")))
            .WillByDefault(ReturnRef(mWaterThirstReduction));
        ON_CALL(mWater, hasAttribute(StrEq("position")))
            .WillByDefault(Return(true));
        ON_CALL(mWater, getAttribute(StrEq("position")))
            .WillByDefault(ReturnRef(mWaterPosition));
    }
};
