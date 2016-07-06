#include "../../../src/logic/jobs/FindWater.hpp"
#include "../LogicTestBase.hpp"

class FindWaterTest : public LogicTestBase
{
};

TEST_F(FindWaterTest, GetDistance_Zero)
{
    FindWater findWater(mJobStack, mWorld, mOwner);

    EXPECT_EQ(0, findWater.getDistance(mWater));
}

TEST_F(FindWaterTest, GetDistance_One)
{
    FindWater findWater(mJobStack, mWorld, mOwner);

    mWaterPosition.set<glm::ivec2>(glm::ivec2(1, 0));

    EXPECT_EQ(1, findWater.getDistance(mWater));
}

// Two consumable water objects, one out of range, collect one, wander, then collect other
// _____
//|SC 
//|   C
//
TEST_F(FindWaterTest, TwoConsumables_OneOutOFRange_CollectOneWanderCollectOther)
{
    mOwnerPerception.set<unsigned int>(2);
    mOwnerThirst.set<unsigned int>(3);

    std::vector<std::unique_ptr<GameObject>> objects;

    Variant object1Position = glm::ivec2(1, 0);
    Variant object1Reduction = (unsigned int)1;
    Variant object1Consumable = true;
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
        ON_CALL(*object, getAttribute("consumable"))
            .WillByDefault(ReturnRef(object1Consumable));
        objects.push_back(std::move(object));
    }

    Variant object2Position = glm::ivec2(3, 1);
    Variant object2Reduction = (unsigned int)2;
    Variant object2Consumable = true;
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
        ON_CALL(*object, getAttribute("consumable"))
            .WillByDefault(ReturnRef(object2Consumable));
        objects.push_back(std::move(object));
    }

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));
      
    // Push find water job onto job stack
    auto findWater = std::make_shared<FindWater>(mJobStack, mWorld, mOwner, mRng);
    mJobStack.push_back(findWater);

    // Collect first object. 
    EXPECT_CALL(mWorld, removeObject(Ref(*objects[0])));
    // Stack: FindWater 
    mJobStack.back()->execute(1000);
    EXPECT_EQ(2, mOwnerThirst.get<unsigned int>());
    objects.erase(objects.begin());

    //This pops the job off the job stack, so we need to add another one
    // to collect the second water object.
    mJobStack.push_back(findWater);

    // Figure out that there's no water close by and start wandering.
    // Stack: FindWater 
    mJobStack.back()->execute(1000);

    // Wander right
    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(3));
    // Stack: FindWater, Wander 
    mJobStack.back()->execute(1000);
    EXPECT_EQ(glm::ivec2(1, 0), mOwnerPosition.get<glm::ivec2>());

    // Detect second object and start moving towards it.
    // Stack: FindWater
    mJobStack.back()->execute(1000);

    // Move towards it.
    // Stack: FindWater, Move
    mJobStack.back()->execute(1000);

    // Keep moving towards it
    // Stack: FindWater, Move
    mJobStack.back()->execute(1000);

    // Stand on top of it
    // Stack: FindWater, Move
    mJobStack.back()->execute(1000);
    EXPECT_EQ(glm::ivec2(3, 1), mOwnerPosition.get<glm::ivec2>());

    // Collect it
    EXPECT_CALL(mWorld, removeObject(Ref(*objects[0]))); 
    // Stack: FindWater
    mJobStack.back()->execute(1000);
    EXPECT_EQ(0, mOwnerThirst.get<unsigned int>());
}

// Entity and consumable on top of each other
TEST_F(FindWaterTest, OwnerAndConsumableOnTopOfEachOther)
{
    mOwnerThirst.set<unsigned int>(1);

    std::vector<std::unique_ptr<GameObject>> objects;

    Variant objectPosition = glm::ivec2(0, 0);
    Variant objectReduction = (unsigned int)1;
    Variant objectConsumable = true;
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
        ON_CALL(*object, getAttribute("consumable"))
            .WillByDefault(ReturnRef(objectConsumable));
        objects.push_back(std::move(object));
    }

    ON_CALL(mWorld, getObjects())
        .WillByDefault(ReturnRef(objects));
       
    auto findWater = std::make_shared<FindWater>(mJobStack, mWorld, mOwner, mRng);
    mJobStack.push_back(findWater);

    // Collect it
    EXPECT_CALL(mWorld, removeObject(Ref(*objects[0]))); 
    mJobStack.back()->execute(1000);
    EXPECT_EQ(0, mOwnerThirst.get<unsigned int>());
}
