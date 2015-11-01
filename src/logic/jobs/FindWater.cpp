#include "FindWater.hpp"

FindWater::FindWater(World &world, Entity &owner)
:
    mWorld(world),
    mOwner(owner),
    mRng(RNG::createTrueRandomRNG())
{
    ASSERT(owner.hasAttribute("perception"), "Owner must have perception attribute");
    ASSERT(owner.hasAttribute("position"), "Owner must have position attribute");
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
        if(object->hasAttribute("thirstReduction") && getDistance(*object) <= getPerception()) 
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

    return Math::manhattanDistance(mOwner["position"].get<glm::ivec2>(), object["position"].get<glm::ivec2>());
}

unsigned int FindWater::getPerception()
{
    return mOwner.getAttribute("perception").get<unsigned int>();
}

void FindWater::consume(GameObject &object)
{
    ASSERT(object.hasAttribute("thirstReduction"), "Object must have the attribute thirstReduction");

    auto thirstReduction = object.getAttribute("thirstReduction").get<unsigned int>();
    auto thirst = mOwner.getAttribute("thirst").get<unsigned int>();
    if(thirst <= thirstReduction)
    {
        mOwner.getAttribute("thirst").set<unsigned int>(0);
    }
    else 
    {
        mOwner.getAttribute("thirst").set<unsigned int>(thirst);
    }

    if(object.hasAttribute("consumable"))
    {
        mWorld.removeObject(object);
    }
}
