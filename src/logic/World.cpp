#include "World.hpp"

World::World()
:
    mLogger(LoggerFactory::createLogger("World", Severity::DEBUG))
{
    (*this)["running"] = true;
    (*this)["cameraPosition"] = glm::ivec2(0, 0);
    (*this)["blockedMap"] = std::unordered_map<glm::ivec2, bool, VectorHash>();
}

// LCOV_EXCL_START
World::~World()
{
}
// LCOV_EXCL_STOP

std::vector<std::unique_ptr<Entity>>& World::getEntities()
{
    return mEntities;
}

void World::addEntity(std::unique_ptr<Entity> entity)
{
    mEntities.push_back(std::move(entity));
}

void World::removeDeadEntities()
{
    mEntities.erase(
        std::remove_if(mEntities.begin(), mEntities.end(), 
            // LCOV_EXCL_START
            [&] (auto &entityPtr) { return entityPtr->hasAttribute("dead"); }
            // LCOV_EXCL_STOP
        ), 
        mEntities.end());
}

std::vector<std::unique_ptr<GameObject>>& World::getObjects()
{
    return mObjects;
}

void World::addObject(std::unique_ptr<GameObject> object)
{
    mObjects.push_back(std::move(object));

    setBlockedMapIfSolid(*mObjects.back(), true);
}

void World::removeObject(GameObject &object)
{
    setBlockedMapIfSolid(object, false);

    mObjects.erase(
        std::remove_if(mObjects.begin(), mObjects.end(),
            // LCOV_EXCL_START
            [&] (auto &objectPtr) { return objectPtr.get() == &object; }
            // LCOV_EXCL_STOP
        ), 
        mObjects.end());
}

void World::setBlockedMapIfSolid(GameObject &object, bool blocked)
{
    if(object.hasAttribute("solid"))
    {
        ASSERT(object["solid"].isOfType<bool>(), "Solid flag must be a bool");

        if(object["solid"].get<bool>())
        {
            ASSERT(object.hasAttribute("position"), "Solid object must have position");
            ASSERT(object["position"].isOfType<glm::ivec2>(), "Position must be a glm::ivec2");

            auto position = object["position"].get<glm::ivec2>();
            auto &blockedMap = 
                (*this)["blockedMap"].get<std::unordered_map<glm::ivec2, bool, VectorHash>>();
            blockedMap[position] = blocked;
        }
    }
}

bool World::isBlocked(glm::ivec2 position)
{
    mLogger->debug(std::string("isBlocked(") + glm::to_string(position) + ")");

    mLogger->debug(std::string("Getting blockedMap reference"));
    auto &blockedMap = 
        (*this)["blockedMap"].get<std::unordered_map<glm::ivec2, bool, VectorHash>>();

    if(blockedMap.count(position) > 0)
    {
        mLogger->debug(std::string("position is in blockedMap"));
        return blockedMap[position];
    }

    mLogger->debug(std::string("position is not in blockedMap"));
    return false;
}
