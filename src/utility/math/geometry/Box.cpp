#include "Box.hpp"

Box::Box(glm::ivec2 position, glm::uvec2 dimensions)
:
    mPosition(position),
    mDimensions(dimensions)
{
    ASSERT(dimensions.x*dimensions.y != 0, "Box must have volume");
}

bool Box::contains(glm::ivec2 position)
{
    return position.x >= mPosition.x 
        && position.y >= mPosition.y
        && mPosition.x + (int)mDimensions.x > position.x
        && mPosition.y + (int)mDimensions.y > position.y; 
}

unsigned int Box::getVolume() const
{
    return mDimensions.x * mDimensions.y;
}

glm::ivec2 Box::getPosition() const
{
    return mPosition;
}

glm::uvec2 Box::getDimensions() const
{
    return mDimensions;
}

