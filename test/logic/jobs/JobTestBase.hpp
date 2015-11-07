#pragma once

#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../mocks/MockEntity.hpp"
#include "../../mocks/MockGameObject.hpp"
#include "../../mocks/MockRNG.hpp"
#include "../LogicTestBase.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 
using ::testing::StrEq; 
using ::testing::Ref; 
using ::testing::_; 

using MockGameObjectType = ::testing::NiceMock<MockGameObject>;
using MockWorldType = ::testing::NiceMock<MockWorld>;
using MockRNGType = ::testing::NiceMock<MockRNG>;

class JobTestBase : public LogicTestBase
{
protected:
    MockRNGType mRng;

    MockGameObjectType mWater;
    Variant mWaterThirstReduction;
    Variant mWaterPosition;

    JobTestBase()
    :
        mWaterThirstReduction((unsigned int)0),
        mWaterPosition(glm::ivec2(0, 0))
    {
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
