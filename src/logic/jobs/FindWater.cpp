#include "FindWater.hpp"

RNG FindWater::cTrueRng = RNG::createTrueRandomRNG();

FindWater::FindWater(JobStack &jobStack, World &world, Entity &owner)
:
    FindWater(jobStack, world, owner, cTrueRng)
{
}

FindWater::FindWater(JobStack &jobStack, World &world, Entity &owner, RNG &rng)
:
    mLogger(LoggerFactory::createLogger("FindWater", Severity::DEBUG)),
    mWorld(world),
    mOwner(owner),
    mRng(rng),
    mEntityUtils(std::make_unique<EntityUtils>()),
    mGameObjectUtils(std::make_unique<GameObjectUtils>()),
    mJobStack(jobStack)
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
    ASSERT(dt == dt, ""); // Getting rid of unused parameter warning

    LOG_DEBUG(mLogger, "Executing...");

    // Check if water source can be found within sensory range
    auto perception = mOwner["perception"].get<unsigned int>();
    auto water = mEntityUtils->getClosestObjectWithAttributeInRange(mWorld, mOwner, "thirstReduction", perception);
    if(water != nullptr) {
        LOG_DEBUG(mLogger, "Water detected.");
        if(getDistance(*water) <= 1)
        {
            LOG_DEBUG(mLogger, "Water is close.");
            mEntityUtils->consumeWater(mWorld, mOwner, *water);
            mJobStack.pop_back();
        } 
        else
        {
            LOG_DEBUG(mLogger, "Water is far away.");
            mJobStack.push_back(
                std::make_unique<Move>(mJobStack, mWorld, mOwner, 
                    (*water)["position"].get<glm::ivec2>()));
        }
    } 
    else 
    {
        LOG_DEBUG(mLogger, "No water in sight.");
        mJobStack.push_back(std::make_unique<Wander>(mJobStack, mWorld, mOwner, mRng));
    }
}

unsigned int FindWater::getDistance(GameObject &object)
{
    ASSERT(object.hasAttribute("position"), "Object must have position");
    ASSERT(object["position"].isOfType<glm::ivec2>(), "Object position must be a glm::ivec2");

    return Math::manhattanDistance(mOwner["position"].get<glm::ivec2>(), 
        object["position"].get<glm::ivec2>());
}
