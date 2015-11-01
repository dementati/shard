#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../../src/logic/jobs/FindWater.hpp"
#include "../../mocks/MockEntity.hpp"
#include "../../mocks/MockGameObject.hpp"
#include "../../mocks/MockRNG.hpp"
#include "../../mocks/MockWorld.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 
using ::testing::StrEq; 
using ::testing::Ref; 

using MockEntityType = ::testing::NiceMock<MockEntity>;
using MockGameObjectType = ::testing::NiceMock<MockGameObject>;
using MockWorldType = ::testing::NiceMock<MockWorld>;
using MockRNGType = ::testing::NiceMock<MockRNG>;

class FindWaterTest : public ::testing::Test
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

    FindWaterTest()
    :
        mOwnerPosition(glm::ivec2(0, 0)),
        mOwnerPerception((unsigned int)1),
        mDefaultTarget(glm::ivec2(0, 1)),
        mOwnerTimeSinceLastStep((unsigned int)0),
        mOwnerSpeed(1.0f),
        mOwnerThirst((unsigned int)0),
        mWaterThirstReduction((unsigned int)0)
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
};

TEST_F(FindWaterTest, GetDistance_Zero)
{
    FindWater findWater(mWorld, mOwner);

    MockGameObjectType object;
    Variant position = glm::ivec2(0,0);
    ON_CALL(object, hasAttribute(StrEq("position")))
        .WillByDefault(Return(true));
    ON_CALL(object, getAttribute(StrEq("position")))
        .WillByDefault(ReturnRef(position));

    EXPECT_EQ(0, findWater.getDistance(object));
}

TEST_F(FindWaterTest, GetDistance_One)
{
    FindWater findWater(mWorld, mOwner);

    MockGameObjectType object;
    Variant position = glm::ivec2(1,0);
    ON_CALL(object, hasAttribute(StrEq("position")))
        .WillByDefault(Return(true));
    ON_CALL(object, getAttribute(StrEq("position")))
        .WillByDefault(ReturnRef(position));

    EXPECT_EQ(1, findWater.getDistance(object));
}

TEST_F(FindWaterTest, Consume_ZeroThirst_ZeroReduction)
{
    FindWater findWater(mWorld, mOwner);

    findWater.consume(mWater);

    EXPECT_EQ(0, mOwnerThirst.get<unsigned int>());
}

TEST_F(FindWaterTest, Consume_ThirstOne_ZeroReduction)
{
    setOwnerThirst(1);

    FindWater findWater(mWorld, mOwner);

    findWater.consume(mWater);

    EXPECT_EQ(1, mOwnerThirst.get<unsigned int>());
}

TEST_F(FindWaterTest, Consume_ThirstOne_ReductionOne)
{
    setOwnerThirst(1);
    setWaterThirstReduction(1);

    FindWater findWater(mWorld, mOwner);

    findWater.consume(mWater);

    EXPECT_EQ(0, mOwnerThirst.get<unsigned int>());
}

TEST_F(FindWaterTest, Consume_ThirstTwo_ReductionOne)
{
    setOwnerThirst(2);
    setWaterThirstReduction(1);

    FindWater findWater(mWorld, mOwner);

    findWater.consume(mWater);

    EXPECT_EQ(1, mOwnerThirst.get<unsigned int>());
}

TEST_F(FindWaterTest, Consume_ThirstOne_ReductionTwo)
{
    setOwnerThirst(1);
    setWaterThirstReduction(2);

    FindWater findWater(mWorld, mOwner);

    findWater.consume(mWater);

    EXPECT_EQ(0, mOwnerThirst.get<unsigned int>());
}

TEST_F(FindWaterTest, Consume_Consumable)
{
    ON_CALL(mWater, hasAttribute(StrEq("consumable")))
        .WillByDefault(Return(true));

    EXPECT_CALL(mWorld, removeObject(Ref(mWater)));

    FindWater findWater(mWorld, mOwner);

    findWater.consume(mWater);
}

TEST_F(FindWaterTest, GetClosestWaterInRange_NoObjects)
{
    std::vector<std::unique_ptr<GameObject>> objects;
    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));
        
    FindWater findWater(mWorld, mOwner);

    EXPECT_EQ(nullptr, findWater.getClosestWaterInRange());
}

TEST_F(FindWaterTest, GetClosestWaterInRange_NoWaterObjects)
{
    std::vector<std::unique_ptr<GameObject>> objects;

    auto object = std::make_unique<MockGameObjectType>();
    ON_CALL(*object, hasAttribute("thirstReduction"))
        .WillByDefault(Return(false));
    objects.push_back(std::move(object));

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));
        
    FindWater findWater(mWorld, mOwner);

    EXPECT_EQ(nullptr, findWater.getClosestWaterInRange());
}

TEST_F(FindWaterTest, GetClosestWaterInRange_ObjectAt0x0)
{
    std::vector<std::unique_ptr<GameObject>> objects;

    Variant objectPosition = glm::ivec2(0, 0);

    auto object = std::make_unique<MockGameObjectType>();
    ON_CALL(*object, hasAttribute("thirstReduction"))
        .WillByDefault(Return(true));
    ON_CALL(*object, hasAttribute("position"))
        .WillByDefault(Return(true));
    ON_CALL(*object, getAttribute("position"))
        .WillByDefault(ReturnRef(objectPosition));
    objects.push_back(std::move(object));

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));
        
    FindWater findWater(mWorld, mOwner);

    EXPECT_EQ(objects[0].get(), findWater.getClosestWaterInRange());
}

TEST_F(FindWaterTest, GetClosestWaterInRange_ObjectAt1x0)
{
    std::vector<std::unique_ptr<GameObject>> objects;

    Variant objectPosition = glm::ivec2(1, 0);

    auto object = std::make_unique<MockGameObjectType>();
    ON_CALL(*object, hasAttribute("thirstReduction"))
        .WillByDefault(Return(true));
    ON_CALL(*object, hasAttribute("position"))
        .WillByDefault(Return(true));
    ON_CALL(*object, getAttribute("position"))
        .WillByDefault(ReturnRef(objectPosition));
    objects.push_back(std::move(object));

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));
        
    FindWater findWater(mWorld, mOwner);

    EXPECT_EQ(objects[0].get(), findWater.getClosestWaterInRange());
}

TEST_F(FindWaterTest, GetClosestWaterInRange_ObjectAt1x1)
{
    std::vector<std::unique_ptr<GameObject>> objects;

    Variant objectPosition = glm::ivec2(1, 1);

    auto object = std::make_unique<MockGameObjectType>();
    ON_CALL(*object, hasAttribute("thirstReduction"))
        .WillByDefault(Return(true));
    ON_CALL(*object, hasAttribute("position"))
        .WillByDefault(Return(true));
    ON_CALL(*object, getAttribute("position"))
        .WillByDefault(ReturnRef(objectPosition));
    objects.push_back(std::move(object));

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));
        
    FindWater findWater(mWorld, mOwner);

    EXPECT_EQ(objects[0].get(), findWater.getClosestWaterInRange());
}

TEST_F(FindWaterTest, GetClosestWaterInRange_ObjectsAt0x0And1x0)
{
    std::vector<std::unique_ptr<GameObject>> objects;


    Variant object1Position = glm::ivec2(1, 0);
    {
        auto object = std::make_unique<MockGameObjectType>();
        ON_CALL(*object, hasAttribute("thirstReduction"))
            .WillByDefault(Return(true));
        ON_CALL(*object, hasAttribute("position"))
            .WillByDefault(Return(true));
        ON_CALL(*object, getAttribute("position"))
            .WillByDefault(ReturnRef(object1Position));
        objects.push_back(std::move(object));
    }

    Variant object2Position = glm::ivec2(0, 0);
    {
        auto object = std::make_unique<MockGameObjectType>();
        ON_CALL(*object, hasAttribute("thirstReduction"))
            .WillByDefault(Return(true));
        ON_CALL(*object, hasAttribute("position"))
            .WillByDefault(Return(true));
        ON_CALL(*object, getAttribute("position"))
            .WillByDefault(ReturnRef(object2Position));
        objects.push_back(std::move(object));
    }

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));
        
    FindWater findWater(mWorld, mOwner);

    EXPECT_EQ(objects[1].get(), findWater.getClosestWaterInRange());
}

TEST_F(FindWaterTest, GetClosestWaterInRange_ObjectOutOfPerception)
{
    std::vector<std::unique_ptr<GameObject>> objects;

    Variant objectPosition = glm::ivec2(2, 0);

    auto object = std::make_unique<MockGameObjectType>();
    ON_CALL(*object, hasAttribute("thirstReduction"))
        .WillByDefault(Return(true));
    ON_CALL(*object, hasAttribute("position"))
        .WillByDefault(Return(true));
    ON_CALL(*object, getAttribute("position"))
        .WillByDefault(ReturnRef(objectPosition));
    objects.push_back(std::move(object));

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));
        
    FindWater findWater(mWorld, mOwner);

    EXPECT_EQ(nullptr, findWater.getClosestWaterInRange());
}

// Two consumable water objects, one out of range, collect one, wander, then collect other
// _____
//|SC 
//|   C
//
TEST_F(FindWaterTest, TwoConsumables_OneOutOFRange_CollectOneWanderCollectOther)
{
    setOwnerPerception(2);
    setOwnerThirst(3);

    std::vector<std::unique_ptr<GameObject>> objects;

    Variant object1Position = glm::ivec2(1, 0);
    Variant object1Reduction = (unsigned int)1;
    {
        auto object = std::make_unique<MockGameObjectType>();
        ON_CALL(*object, hasAttribute("thirstReduction"))
            .WillByDefault(Return(true));
        ON_CALL(*object, getAttribute("thirstReduction"))
            .WillByDefault(ReturnRef(object1Reduction));
        ON_CALL(*object, hasAttribute("position"))
            .WillByDefault(Return(true));
        ON_CALL(*object, getAttribute("position"))
            .WillByDefault(ReturnRef(object1Position));
        ON_CALL(*object, hasAttribute("consumable"))
            .WillByDefault(Return(true));
        objects.push_back(std::move(object));
    }

    Variant object2Position = glm::ivec2(3, 1);
    Variant object2Reduction = (unsigned int)2;
    {
        auto object = std::make_unique<MockGameObjectType>();
        ON_CALL(*object, hasAttribute("thirstReduction"))
            .WillByDefault(Return(true));
        ON_CALL(*object, getAttribute("thirstReduction"))
            .WillByDefault(ReturnRef(object2Reduction));
        ON_CALL(*object, hasAttribute("position"))
            .WillByDefault(Return(true));
        ON_CALL(*object, getAttribute("position"))
            .WillByDefault(ReturnRef(object2Position));
        ON_CALL(*object, hasAttribute("consumable"))
            .WillByDefault(Return(true));
        objects.push_back(std::move(object));
    }

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));
       
    FindWater findWater(mWorld, mOwner, mRng);

    // Collect first object
    EXPECT_CALL(mWorld, removeObject(Ref(*objects[0]))); 
    findWater.execute(1000);
    EXPECT_EQ(2, mOwnerThirst.get<unsigned int>());
    objects.erase(objects.begin());

    // Wander right
    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(3));
    findWater.execute(1000);
    EXPECT_EQ(glm::ivec2(1, 0), mOwnerPosition.get<glm::ivec2>());

    // Detect second object and move towards it
    findWater.execute(1000);

    // Keep moving towards it
    findWater.execute(1000);

    // Collect it
    EXPECT_CALL(mWorld, removeObject(Ref(*objects[0]))); 
    findWater.execute(1000);
    EXPECT_EQ(0, mOwnerThirst.get<unsigned int>());
}
