#include "Entity.hpp"

// LCOV_EXCL_START
Entity::Entity(const std::string renderableId)
    : renderableId(renderableId)
{
}

Entity::Entity(Entity&& entity)
    : needs(std::move(entity.needs)), position(entity.position), renderableId(entity.renderableId)
{
}
// LCOV_EXCL_STOP

void Entity::addNeed(std::unique_ptr<Need> need)
{
    needs.push_back(std::move(need));
}

Need& Entity::selectNeed()
{
    assert(needs.size() != 0 && "Can't select a need from an entity that has no needs.");

    std::sort(needs.begin(), needs.end(), [](auto &a, auto &b)
    {
        return a->getIntensity() < b->getIntensity();
    });

    return *needs.back();
}

const std::string Entity::unitName() const
{
    return std::string("Entity");
}
