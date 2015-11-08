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
    mRng(rng),
    mEntityUtils(std::make_unique<EntityUtils>()),
    mGameObjectUtils(std::make_unique<GameObjectUtils>())
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
    auto perception = mOwner["perception"].get<unsigned int>();
    auto water = mEntityUtils->getClosestObjectWithAttributeInRange(mWorld, mOwner, "thirstReduction", perception);
    if(water != nullptr) {
        mLogger->debug("Water detected.");
        if(getDistance(*water) <= 1)
        {
            mLogger->debug("Water is close.");
            mEntityUtils->consumeWater(mWorld, mOwner, *water);
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

unsigned int FindWater::getDistance(GameObject &object)
{
    ASSERT(object.hasAttribute("position"), "Object must have position");
    ASSERT(object["position"].isOfType<glm::ivec2>(), "Object position must be a glm::ivec2");

    return Math::manhattanDistance(mOwner["position"].get<glm::ivec2>(), object["position"].get<glm::ivec2>());
}
