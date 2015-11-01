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
    std::vector<std::reference_wrapper<GameObject>> waterItemsInRange;
    for(auto &item : mWorld.getItems())
    {
        if(item->hasAttribute("thirstReduction") && getDistance(*item) <= getPerception()) 
        {
            waterItemsInRange.push_back(std::ref(*item));
        }
    }

    if(waterItemsInRange.empty())
    {
        return nullptr;
    }

    return &(*std::min_element(waterItemsInRange.begin(), waterItemsInRange.end(), 
        [&] (auto &itemA, auto &itemB) {
            return this->getDistance(itemA) < this->getDistance(itemB);
        })).get(); 
}

unsigned int FindWater::getDistance(GameObject &item)
{
    ASSERT(item.hasAttribute("position"), "Item must have position");

    return Math::manhattanDistance(mOwner["position"].get<glm::ivec2>(), item["position"].get<glm::ivec2>());
}

unsigned int FindWater::getPerception()
{
    return mOwner.getAttribute("perception").get<unsigned int>();
}

void FindWater::consume(GameObject &item)
{
    ASSERT(item.hasAttribute("thirstReduction"), "Item must have the attribute thirstReduction");

    auto thirstReduction = item.getAttribute("thirstReduction").get<unsigned int>();
    auto thirst = mOwner.getAttribute("thirst").get<unsigned int>();
    if(thirst <= thirstReduction)
    {
        mOwner.getAttribute("thirst").set<unsigned int>(0);
    }
    else 
    {
        mOwner.getAttribute("thirst").set<unsigned int>(thirst);
    }

    if(item.hasAttribute("consumable"))
    {
        mWorld.removeItem(item);
    }
}
