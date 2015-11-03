#include "../../../src/logic/jobs/FindWater.hpp"
#include "JobTestBase.hpp"

class FindWaterTest : public JobTestBase
{
};

TEST_F(FindWaterTest, GetDistance_Zero)
{
    FindWater findWater(mWorld, mOwner);

    EXPECT_EQ(0, findWater.getDistance(mWater));
}

TEST_F(FindWaterTest, GetDistance_One)
{
    FindWater findWater(mWorld, mOwner);

    setWaterPosition(glm::ivec2(1, 0));

    EXPECT_EQ(1, findWater.getDistance(mWater));
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
    setWaterConsumable(true);

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

// Entity and consumable on top of each other
TEST_F(FindWaterTest, OwnerAndConsumableOnTopOfEachOther)
{
    setOwnerThirst(1);

    std::vector<std::unique_ptr<GameObject>> objects;

    Variant objectPosition = glm::ivec2(0, 0);
    Variant objectReduction = (unsigned int)1;
    {
        auto object = std::make_unique<MockGameObjectType>();
        ON_CALL(*object, hasAttribute("thirstReduction"))
            .WillByDefault(Return(true));
        ON_CALL(*object, getAttribute("thirstReduction"))
            .WillByDefault(ReturnRef(objectReduction));
        ON_CALL(*object, hasAttribute("position"))
            .WillByDefault(Return(true));
        ON_CALL(*object, getAttribute("position"))
            .WillByDefault(ReturnRef(objectPosition));
        ON_CALL(*object, hasAttribute("consumable"))
            .WillByDefault(Return(true));
        objects.push_back(std::move(object));
    }

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));
       
    FindWater findWater(mWorld, mOwner, mRng);

    // Collect it
    EXPECT_CALL(mWorld, removeObject(Ref(*objects[0]))); 
    findWater.execute(1000);
    EXPECT_EQ(0, mOwnerThirst.get<unsigned int>());
}
