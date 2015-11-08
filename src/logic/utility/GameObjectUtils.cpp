#include "GameObjectUtils.hpp"

GameObjectUtils::~GameObjectUtils()
{
}

Box GameObjectUtils::getPerceptionBox(GameObject &object)
{
    ASSERT(object.hasAttribute("perception"), "Object must have perception");
    ASSERT(object["perception"].isOfType<unsigned int>(), "Perception must be an unsigned int");
    int perception = object["perception"].get<unsigned int>();
    ASSERT(perception > 0, "Cannot navigate with 0 perception");
    ASSERT(object.hasAttribute("position"), "Object must have a position");
    ASSERT(object["position"].isOfType<glm::ivec2>(), "Position must be a glm::ivec2");

    glm::ivec2 position = object["position"].get<glm::ivec2>();

    return Math::getCenteredBox(position, perception);
}
