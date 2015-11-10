#include "EntityUtils.hpp"

EntityUtils::~EntityUtils()
{
}

void EntityUtils::updateStepTimer(Entity &entity, unsigned int dt)
{
    ASSERT(entity.hasAttribute("timeSinceLastStep"), "Entity must have timeSinceLastStep");
    ASSERT(entity["timeSinceLastStep"].isOfType<unsigned int>(), "timeSinceLastStep must be an unsigned int");

    unsigned int timeSinceLastStep = entity["timeSinceLastStep"].get<unsigned int>() + dt;
    entity["timeSinceLastStep"].set<unsigned int>(timeSinceLastStep);
}

bool EntityUtils::canMove(Entity &entity)
{
    ASSERT(entity.hasAttribute("timeSinceLastStep"), "Entity must have timeSinceLastStep");
    ASSERT(entity["timeSinceLastStep"].isOfType<unsigned int>(), "timeSinceLastStep must be an unsigned int");
    ASSERT(entity.hasAttribute("speed"), "Entity must have speed");
    ASSERT(entity["speed"].isOfType<float>(), "speed must be a float");

    unsigned int timeSinceLastStep = entity["timeSinceLastStep"].get<unsigned int>();
    unsigned int stepLimit = (unsigned int)(1000.0f / entity["speed"].get<float>());
    return timeSinceLastStep >= stepLimit;
}

void EntityUtils::move(World &world, Entity &entity, glm::ivec2 deltaPosition)
{
    ASSERT(entity.hasAttribute("position"), "Entity must have a position");
    ASSERT(entity["position"].isOfType<glm::ivec2>(), "Position must be a glm::ivec2");
    ASSERT(entity.hasAttribute("timeSinceLastStep"), "Entity must have timeSinceLastStep");
    ASSERT(entity["timeSinceLastStep"].isOfType<unsigned int>(), "timeSinceLastStep must be an unsigned int");
    ASSERT(deltaPosition != glm::ivec2(0, 0), "deltaPosition cannot be (0, 0)");

    auto position = entity["position"].get<glm::ivec2>() + deltaPosition;

    entity["timeSinceLastStep"].set<unsigned int>(0);

    if(!world.isBlocked(position))
    {
        entity["position"].set<glm::ivec2>(position);
    }
}

GameObject* EntityUtils::getClosestObjectWithAttributeInRange(World &world, Entity &entity, std::string attribute, 
    unsigned int range)
{
    ASSERT(entity.hasAttribute("position"), "Entity must have position");
    ASSERT(entity["position"].isOfType<glm::ivec2>(), "Position must be a glm::ivec2");
    ASSERT(range > 0, "Range must be positive");

    auto entityPosition = entity["position"].get<glm::ivec2>();

    auto minDistance = -1;
    GameObject* minObject = nullptr;

    Box rangeBox = Math::getCenteredBox(entityPosition, range);
    for(auto &objectPtr : world.getObjects())
    {
        auto &object = *objectPtr;

        if(object.hasAttribute(attribute))
        {
            ASSERT(object.hasAttribute("position"), "Object with attribute " << attribute << " must also have a position");
            ASSERT(object["position"].isOfType<glm::ivec2>(), "Object position must be a glm::ivec2");

            auto objectPosition = object["position"].get<glm::ivec2>();

            if(rangeBox.contains(objectPosition))
            {
                auto distance = Math::manhattanDistance(entityPosition, objectPosition);

                if(minDistance == -1 || distance < (unsigned int)minDistance)
                {
                    minDistance = distance;
                    minObject = objectPtr.get();
                }
            }
        }
    }

    return minObject;
}

void EntityUtils::consumeWater(World &world, Entity &entity, GameObject &water)
{
    ASSERT(water.hasAttribute("thirstReduction"), "Object must have the attribute thirstReduction");
    ASSERT(water["thirstReduction"].isOfType<unsigned int>(), "Object thirst reduction must be a unsigned int");
    ASSERT(entity.hasAttribute("thirst"), "Entity must have thirst attribute.");
    ASSERT(entity["thirst"].isOfType<unsigned int>(), "Thirst must be an unsigned int");

    auto thirstReduction = water.getAttribute("thirstReduction").get<unsigned int>();
    auto thirst = entity.getAttribute("thirst").get<unsigned int>();
    if(thirst <= thirstReduction)
    {
        entity.getAttribute("thirst").set<unsigned int>(0);
    }
    else 
    {
        entity.getAttribute("thirst").set<unsigned int>(thirst - thirstReduction);
    }

    if(water.hasAttribute("consumable"))
    {
        ASSERT(water["consumable"].isOfType<bool>(), "Consumable flag must be a bool");
        
        if(water["consumable"].get<bool>())
        {
            world.removeObject(water);
        }
    }
}

void EntityUtils::consumeBlood(World &world, Entity &entity, GameObject &human)
{
    ASSERT(human.hasAttribute("blood"), "Object must have the attribute blood");
    ASSERT(human["blood"].isOfType<unsigned int>(), "Object thirst reduction must be a unsigned int");
    ASSERT(entity.hasAttribute("thirst"), "Entity must have thirst attribute.");
    ASSERT(entity["thirst"].isOfType<unsigned int>(), "Thirst must be an unsigned int");

    auto thirstReduction = human.getAttribute("blood").get<unsigned int>();
    auto thirst = entity.getAttribute("thirst").get<unsigned int>();
    if(thirst <= thirstReduction)
    {
        entity.getAttribute("thirst").set<unsigned int>(0);
    }
    else 
    {
        entity.getAttribute("thirst").set<unsigned int>(thirst - thirstReduction);
    }

	world.removeObject(human);
    /*if(blood.hasAttribute("consumable"))
    {
        ASSERT(blood["consumable"].isOfType<bool>(), "Consumable flag must be a bool");
        
        if(blood["consumable"].get<bool>())
        {
            world.removeObject(blood);
        }
    }*/
}
