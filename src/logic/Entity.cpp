#include "Entity.hpp"

// LCOV_EXCL_START
Entity::Entity(const std::string renderableId)
    : renderableId(renderableId)
{
}

const std::string Entity::getRenderableId()
{
    return renderableId;
}

const std::string Entity::unitName() const
{
    return std::string("Entity");
}
// LCOV_EXCL_STOP
