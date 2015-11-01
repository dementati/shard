#include "FindWater.hpp"

FindWater::FindWater(World &world, Entity &owner)
:
    mWorld(world),
    mOwner(owner),
    mRng(RNG::createTrueRandomRNG())
{
    ASSERT(owner.hasAttribute("perception"), "Owner must have perception attribute");
    ASSERT(owner["perception"].isOfType<unsigned int>(), "Owner perception must be an unsigned int");
    ASSERT(owner.hasAttribute("position"), "Owner must have position attribute");
    ASSERT(owner["position"].isOfType<glm::ivec2>(), "Owner position must be a glm::ivec2");
    ASSERT(owner.hasAttribute("thirst"), "Owner must have position attribute");
    ASSERT(owner["thirst"].isOfType<unsigned int>(), "Owner thirst must be an unsigned int");
}

void FindWater::execute(unsigned int dt)
{
    // Check if water source can be found within sensory range
    auto water = getClosestWaterInRange();
    if(water != nullptr) {
        if(getDistance(*water) == 1)
        {
            consume(*water);
        } 
        else
        {
            Move move(mWorld, mOwner, (*water)["position"].get<glm::ivec2>());
            move.execute(dt);
        }
    } 
    else 
    {
        Wander wander(mWorld, mOwner, mRng);
        wander.execute(dt);
    }
}

GameObject* FindWater::getClosestWaterInRange()
{
    std::vector<std::reference_wrapper<GameObject>> waterObjectsInRange;
    for(auto &object : mWorld.getObjects())
    {
        auto perception = mOwner["perception"].get<unsigned int>();
        if(object->hasAttribute("thirstReduction") && getDistance(*object) <= perception) 
        {
            waterObjectsInRange.push_back(std::ref(*object));
        }
    }

    if(waterObjectsInRange.empty())
    {
        return nullptr;
    }

    return &(*std::min_element(waterObjectsInRange.begin(), waterObjectsInRange.end(), 
        [&] (auto &objectA, auto &objectB) {
            return this->getDistance(objectA) < this->getDistance(objectB);
        })).get(); 
}

unsigned int FindWater::getDistance(GameObject &object)
{
    ASSERT(object.hasAttribute("position"), "Object must have position");
    ASSERT(object["position"].isOfType<glm::ivec2>(), "Object position must be a glm::ivec2");

    return Math::manhattanDistance(mOwner["position"].get<glm::ivec2>(), object["position"].get<glm::ivec2>());
}

void FindWater::consume(GameObject &water)
{
    ASSERT(water.hasAttribute("thirstReduction"), "Object must have the attribute thirstReduction");
    ASSERT(water["thirstReduction"].isOfType<unsigned int>(), "Object thirst reduction must be a unsigned int");

    auto thirstReduction = water.getAttribute("thirstReduction").get<unsigned int>();
    auto thirst = mOwner.getAttribute("thirst").get<unsigned int>();
    if(thirst <= thirstReduction)
    {
        mOwner.getAttribute("thirst").set<unsigned int>(0);
    }
    else 
    {
        mOwner.getAttribute("thirst").set<unsigned int>(thirst);
    }

    if(water.hasAttribute("consumable"))
    {
        mWorld.removeObject(water);
    }
}
