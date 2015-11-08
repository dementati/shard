#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../../src/logic/utility/EntityUtils.hpp"
#include "../LogicTestBase.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 
using ::testing::StrEq; 

class EntityUtilsTest : public LogicTestBase
{
protected:
    EntityUtilsTest()
    {
    }
};

TEST_F(EntityUtilsTest, updateStepTimer_Zero)
{
    EntityUtils utils;
    utils.updateStepTimer(mOwner, 0);

    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(EntityUtilsTest, updateStepTimer_One)
{
    EntityUtils utils;
    utils.updateStepTimer(mOwner, 1);

    EXPECT_EQ(1, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(EntityUtilsTest, updateStepTimer_OneTwo)
{
    EntityUtils utils;
    utils.updateStepTimer(mOwner, 1);
    utils.updateStepTimer(mOwner, 2);

    EXPECT_EQ(3, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(EntityUtilsTest, canMove_OneSecondMinusOneMs)
{
    mOwnerTimeSinceLastStep.set<unsigned int>(999);

    EntityUtils utils;

    EXPECT_FALSE(utils.canMove(mOwner));
}

TEST_F(EntityUtilsTest, canMove_OneSecond)
{
    mOwnerTimeSinceLastStep.set<unsigned int>(1000);

    EntityUtils utils;

    EXPECT_TRUE(utils.canMove(mOwner));
}

TEST_F(EntityUtilsTest, canMove_HalfSpeed_TwoSecondsMinusOneMs)
{
    mOwnerTimeSinceLastStep.set<unsigned int>(1999);
    mOwnerSpeed.set<float>(0.5f);

    EntityUtils utils;

    EXPECT_FALSE(utils.canMove(mOwner));
}

TEST_F(EntityUtilsTest, canMove_HalfSpeed_TwoSeconds)
{
    mOwnerTimeSinceLastStep.set<unsigned int>(2000);
    mOwnerSpeed.set<float>(0.5f);

    EntityUtils utils;

    EXPECT_TRUE(utils.canMove(mOwner));
}

TEST_F(EntityUtilsTest, move_position0x0_deltaPosition1x0)
{
    EntityUtils utils;

    utils.move(mWorld, mOwner, glm::ivec2(1, 0));

    EXPECT_EQ(glm::ivec2(1, 0), mOwnerPosition.get<glm::ivec2>());
}

TEST_F(EntityUtilsTest, move_position0x0_deltaPosition0xMinus1)
{
    EntityUtils utils;

    utils.move(mWorld, mOwner, glm::ivec2(0, -1));

    EXPECT_EQ(glm::ivec2(0, -1), mOwnerPosition.get<glm::ivec2>());
}

TEST_F(EntityUtilsTest, move_positionMinus1xMinus1_deltaPosition1x0)
{
    mOwnerPosition.set<glm::ivec2>(glm::ivec2(-1, -1));

    EntityUtils utils;

    utils.move(mWorld, mOwner, glm::ivec2(1, 0));

    EXPECT_EQ(glm::ivec2(0, -1), mOwnerPosition.get<glm::ivec2>());
}

TEST_F(EntityUtilsTest, move_position1x1_deltaPositionMinus1x0)
{
    mOwnerPosition.set<glm::ivec2>(glm::ivec2(1, 1));

    EntityUtils utils;

    utils.move(mWorld, mOwner, glm::ivec2(1, 0));

    EXPECT_EQ(glm::ivec2(2, 1), mOwnerPosition.get<glm::ivec2>());
}

TEST_F(EntityUtilsTest, move_resetTimeSinceLastStep)
{
    mOwnerTimeSinceLastStep.set<unsigned int>(1);

    EntityUtils utils;

    utils.move(mWorld, mOwner, glm::ivec2(1, 0));

    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(EntityUtilsTest, consumeWater_ZeroThirst_ZeroReduction)
{
    EntityUtils utils;

    utils.consumeWater(mWorld, mOwner, mWater);

    EXPECT_EQ(0, mOwnerThirst.get<unsigned int>());
}

TEST_F(EntityUtilsTest, consumeWater_ThirstOne_ZeroReduction)
{
    mOwnerThirst.set<unsigned int>(1);
    
    EntityUtils utils;

    utils.consumeWater(mWorld, mOwner, mWater);

    EXPECT_EQ(1, mOwnerThirst.get<unsigned int>());
}

TEST_F(EntityUtilsTest, consumeWater_ThirstOne_ReductionOne)
{
    mOwnerThirst.set<unsigned int>(1);
    mWaterThirstReduction.set<unsigned int>(1);

    EntityUtils utils;

    utils.consumeWater(mWorld, mOwner, mWater);

    EXPECT_EQ(0, mOwnerThirst.get<unsigned int>());
}

TEST_F(EntityUtilsTest, consumeWater_ThirstTwo_ReductionOne)
{
    mOwnerThirst.set<unsigned int>(2);
    mWaterThirstReduction.set<unsigned int>(1);

    EntityUtils utils;

    utils.consumeWater(mWorld, mOwner, mWater);

    EXPECT_EQ(1, mOwnerThirst.get<unsigned int>());
}

TEST_F(EntityUtilsTest, consumeWater_ThirstOne_ReductionTwo)
{
    mOwnerThirst.set<unsigned int>(1);
    mWaterThirstReduction.set<unsigned int>(2);

    EntityUtils utils;

    utils.consumeWater(mWorld, mOwner, mWater);

    EXPECT_EQ(0, mOwnerThirst.get<unsigned int>());
}

TEST_F(EntityUtilsTest, consumeWater_Consumable)
{
    Variant waterConsumable = true;

    ON_CALL(mWater, hasAttribute("consumable"))
        .WillByDefault(Return(true));
    ON_CALL(mWater, getAttribute("consumable"))
        .WillByDefault(ReturnRef(waterConsumable));

    EXPECT_CALL(mWorld, removeObject(Ref(mWater)));

    EntityUtils utils;

    utils.consumeWater(mWorld, mOwner, mWater);
}

TEST_F(EntityUtilsTest, getClosestObjectWithAttributeInRange_NoObjects)
{
    std::vector<std::unique_ptr<GameObject>> objects;
    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));
        
    EntityUtils utils;

    EXPECT_EQ(nullptr, utils.getClosestObjectWithAttributeInRange(mWorld, mOwner, "", 1));
}

TEST_F(EntityUtilsTest, getClosestObjectWithAttributeInRange_NoObjectsWithAttribute)
{
    std::string attribute = "";

    std::vector<std::unique_ptr<GameObject>> objects;

    auto object = std::make_unique<MockGameObjectType>();
    ON_CALL(*object, hasAttribute(attribute))
        .WillByDefault(Return(false));
    objects.push_back(std::move(object));

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));

    EntityUtils utils;

    EXPECT_EQ(nullptr, utils.getClosestObjectWithAttributeInRange(mWorld, mOwner, attribute, 1));
}

TEST_F(EntityUtilsTest, getClosestObjectWithAttributeInRange_ObjectWithAttributeAt0x0)
{
    std::string attribute = "";

    std::vector<std::unique_ptr<GameObject>> objects;

    Variant objectPosition = glm::ivec2(0, 0);

    auto object = std::make_unique<MockGameObjectType>();
    ON_CALL(*object, hasAttribute(attribute))
        .WillByDefault(Return(true));
    ON_CALL(*object, hasAttribute("position"))
        .WillByDefault(Return(true));
    ON_CALL(*object, getAttribute("position"))
        .WillByDefault(ReturnRef(objectPosition));
    objects.push_back(std::move(object));

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));

    EntityUtils utils;

    EXPECT_EQ(objects[0].get(), 
        utils.getClosestObjectWithAttributeInRange(mWorld, mOwner, attribute, 1));
}

TEST_F(EntityUtilsTest, getClosestObjectWithAttributeInRange_ObjectWithAttributeAt1x0)
{
    std::string attribute = "";

    std::vector<std::unique_ptr<GameObject>> objects;

    Variant objectPosition = glm::ivec2(1, 0);

    auto object = std::make_unique<MockGameObjectType>();
    ON_CALL(*object, hasAttribute(attribute))
        .WillByDefault(Return(true));
    ON_CALL(*object, hasAttribute("position"))
        .WillByDefault(Return(true));
    ON_CALL(*object, getAttribute("position"))
        .WillByDefault(ReturnRef(objectPosition));
    objects.push_back(std::move(object));

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));

    EntityUtils utils;

    EXPECT_EQ(objects[0].get(), 
        utils.getClosestObjectWithAttributeInRange(mWorld, mOwner, attribute, 1));
}

TEST_F(EntityUtilsTest, getClosestObjectWithAttributeInRange_ObjectWithAttributeAt1x1)
{
    std::string attribute = "";

    std::vector<std::unique_ptr<GameObject>> objects;

    Variant objectPosition = glm::ivec2(1, 1);

    auto object = std::make_unique<MockGameObjectType>();
    ON_CALL(*object, hasAttribute(attribute))
        .WillByDefault(Return(true));
    ON_CALL(*object, hasAttribute("position"))
        .WillByDefault(Return(true));
    ON_CALL(*object, getAttribute("position"))
        .WillByDefault(ReturnRef(objectPosition));
    objects.push_back(std::move(object));

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));

    EntityUtils utils;

    EXPECT_EQ(objects[0].get(), 
        utils.getClosestObjectWithAttributeInRange(mWorld, mOwner, attribute, 1));
}

TEST_F(EntityUtilsTest, getClosestObjectWithAttributeInRange_objectsWithAttributeAt0x0And1x0)
{
    std::string attribute = "";

    std::vector<std::unique_ptr<GameObject>> objects;

    Variant object1Position = glm::ivec2(1, 0);
    {
        auto object = std::make_unique<MockGameObjectType>();
        ON_CALL(*object, hasAttribute(attribute))
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
        ON_CALL(*object, hasAttribute(attribute))
            .WillByDefault(Return(true));
        ON_CALL(*object, hasAttribute("position"))
            .WillByDefault(Return(true));
        ON_CALL(*object, getAttribute("position"))
            .WillByDefault(ReturnRef(object2Position));
        objects.push_back(std::move(object));
    }

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));
        
    EntityUtils utils;

    EXPECT_EQ(objects[1].get(), 
        utils.getClosestObjectWithAttributeInRange(mWorld, mOwner, attribute, 1));
}

TEST_F(EntityUtilsTest, getClosestObjectWithAttributeInRange_ObjectWithAttribute2x0_Range1)
{
    std::string attribute = "";

    std::vector<std::unique_ptr<GameObject>> objects;

    Variant objectPosition = glm::ivec2(2, 0);

    auto object = std::make_unique<MockGameObjectType>();
    ON_CALL(*object, hasAttribute(attribute))
        .WillByDefault(Return(true));
    ON_CALL(*object, hasAttribute("position"))
        .WillByDefault(Return(true));
    ON_CALL(*object, getAttribute("position"))
        .WillByDefault(ReturnRef(objectPosition));
    objects.push_back(std::move(object));

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));

    EntityUtils utils;

    EXPECT_EQ(nullptr, 
        utils.getClosestObjectWithAttributeInRange(mWorld, mOwner, attribute, 1));
}

TEST_F(EntityUtilsTest, getClosestObjectWithAttributeInRange_ObjectWithAttribute2x0_Range2)
{
    std::string attribute = "";

    std::vector<std::unique_ptr<GameObject>> objects;

    Variant objectPosition = glm::ivec2(2, 0);

    auto object = std::make_unique<MockGameObjectType>();
    ON_CALL(*object, hasAttribute(attribute))
        .WillByDefault(Return(true));
    ON_CALL(*object, hasAttribute("position"))
        .WillByDefault(Return(true));
    ON_CALL(*object, getAttribute("position"))
        .WillByDefault(ReturnRef(objectPosition));
    objects.push_back(std::move(object));

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));

    EntityUtils utils;

    EXPECT_EQ(objects[0].get(), 
        utils.getClosestObjectWithAttributeInRange(mWorld, mOwner, attribute, 2));
}

TEST_F(EntityUtilsTest, getClosestObjectWithAttributeInRange_ObjectWithAttribute3x0_Range2)
{
    std::string attribute = "";

    std::vector<std::unique_ptr<GameObject>> objects;

    Variant objectPosition = glm::ivec2(3, 0);

    auto object = std::make_unique<MockGameObjectType>();
    ON_CALL(*object, hasAttribute(attribute))
        .WillByDefault(Return(true));
    ON_CALL(*object, hasAttribute("position"))
        .WillByDefault(Return(true));
    ON_CALL(*object, getAttribute("position"))
        .WillByDefault(ReturnRef(objectPosition));
    objects.push_back(std::move(object));

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));

    EntityUtils utils;

    EXPECT_EQ(nullptr, 
        utils.getClosestObjectWithAttributeInRange(mWorld, mOwner, attribute, 2));
}

TEST_F(EntityUtilsTest, getClosestObjectWithAttributeInRange_objectsWithAndWithoutAttribute)
{
    std::string attribute = "";

    std::vector<std::unique_ptr<GameObject>> objects;

    Variant object1Position = glm::ivec2(1, 0);
    {
        auto object = std::make_unique<MockGameObjectType>();
        ON_CALL(*object, hasAttribute(attribute))
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
        ON_CALL(*object, hasAttribute(attribute))
            .WillByDefault(Return(false));
        ON_CALL(*object, hasAttribute("position"))
            .WillByDefault(Return(true));
        ON_CALL(*object, getAttribute("position"))
            .WillByDefault(ReturnRef(object2Position));
        objects.push_back(std::move(object));
    }

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));
        
    EntityUtils utils;

    EXPECT_EQ(objects[0].get(), 
        utils.getClosestObjectWithAttributeInRange(mWorld, mOwner, attribute, 1));
}
