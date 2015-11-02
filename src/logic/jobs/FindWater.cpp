#include "FindWater.hpp"

RNG FindWater::cTrueRng = RNG::createTrueRandomRNG();

FindWater::FindWater(World &world, Entity &owner)
:
    FindWater(world, owner, cTrueRng)
{
}

FindWater::FindWater(World &world, Entity &owner, RNG &rng)
:
    mLogger(LoggerFactory::createLogger("FindWater", Severity::DEBUG)),
    mWorld(world),
    mOwner(owner),
    mRng(rng)
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
    mLogger->debug("Executing...");

    // Check if water source can be found within sensory range
    auto water = getClosestWaterInRange();
    if(water != nullptr) {
        mLogger->debug("Water detected.");
        if(getDistance(*water) <= 1)
        {
            mLogger->debug("Water is close.");
            consume(*water);
        } 
        else
        {
            mLogger->debug("Water is far away.");
            Move move(mWorld, mOwner, (*water)["position"].get<glm::ivec2>());
            move.execute(dt);
        }
    } 
    else 
    {
        mLogger->debug("No water in sight.");
        Wander wander(mWorld, mOwner, mRng);
        wander.execute(dt);
    }
}

GameObject* FindWater::getClosestWaterInRange()
{
    mLogger->debug("Finding closest water in range...");

    mLogger->debug(std::string("Total number of game objects: ") + glm::to_string((int)mWorld.getObjects().size()));
    std::vector<std::reference_wrapper<GameObject>> waterObjectsInRange;
    for(auto &object : mWorld.getObjects())
    {
        auto perception = mOwner["perception"].get<unsigned int>();
        mLogger->debug(std::string("Perception: ") + glm::to_string(perception));
        if(object->hasAttribute("thirstReduction") 
            && GameObjectUtils::getPerceptionBox(mOwner).contains((*object)["position"].get<glm::ivec2>())) 
        {
            mLogger->debug("Water object in range found.");
            waterObjectsInRange.push_back(std::ref(*object));
        } 
        else
        {
            mLogger->debug("Object found, but it's not water or it's not in range.");
        }
    }
    mLogger->debug(std::string("Number of water objects in range: ") + glm::to_string((int)waterObjectsInRange.size()));

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

    mLogger->debug("Consuming...");

    auto thirstReduction = water.getAttribute("thirstReduction").get<unsigned int>();
    auto thirst = mOwner.getAttribute("thirst").get<unsigned int>();
    if(thirst <= thirstReduction)
    {
        mOwner.getAttribute("thirst").set<unsigned int>(0);
    }
    else 
    {
        mOwner.getAttribute("thirst").set<unsigned int>(thirst - thirstReduction);
    }

    if(water.hasAttribute("consumable"))
    {
        mWorld.removeObject(water);
    }
}
