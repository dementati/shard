#include "GameObjectFactory.hpp"

void GameObjectFactory::createHuman(World &world, glm::ivec2 position)
{
    auto human = std::make_unique<Entity>();

    // Add attributes
    human->addAttribute("position", position);
    human->addAttribute("thirst", (unsigned int)0);
    human->addAttribute("renderableId", std::string("human"));

    // Add background jobs

    // Add needs
    human->add(CopyableNeed(Thirst(world, *human)));

    world.addEntity(std::move(human));
}
