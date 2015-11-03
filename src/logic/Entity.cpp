#include "Entity.hpp"

// LCOV_EXCL_START
Entity::Entity()
:
    mNeeds(std::vector<CopyableNeed>())
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

bool Entity::hasNeeds()
{
    return !mNeeds.empty();
}
