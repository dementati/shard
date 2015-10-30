#include "Entity.hpp"

// LCOV_EXCL_START
Entity::Entity(const std::string renderableId)
: 
    mNeeds(std::vector<CopyableNeed>()),
    mPosition(glm::ivec2(0, 0)),
    mRenderableId(renderableId)
{
}

Entity::~Entity()
{
}
// LCOV_EXCL_STOP

void Entity::add(CopyableNeed need)
{
    mNeeds.push_back(need);
}

Need& Entity::selectNeed()
{
    ASSERT(mNeeds.size() != 0, "Can't select a need from an entity that has no needs.");

    std::sort(mNeeds.begin(), mNeeds.end(), [](auto &a, auto &b)
    {
        return a->getIntensity() < b->getIntensity();
    });

    return *mNeeds.back();
}

glm::ivec2 Entity::getPosition()
{
    return mPosition;
}

void Entity::setPosition(glm::ivec2 position)
{
    mPosition = position;
}

// LCOV_EXCL_START
const std::string Entity::getRenderableId()
{
    return mRenderableId;
}
// LCOV_EXCL_STOP
