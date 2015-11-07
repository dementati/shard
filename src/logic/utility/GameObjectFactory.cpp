#include "GameObjectFactory.hpp"

// LCOV_EXCL_START <- This class is constantly in flux, too much work to keep updated tests
void GameObjectFactory::createPlayer(World &world, InputSystem &input, glm::ivec2 position)
{
    auto player = std::make_unique<Entity>();

    // Add attributes
    player->addAttribute("position", position);
    player->addAttribute("renderableId", std::string("player"));
    player->addAttribute("timeSinceLastStep", (unsigned int)0);
    player->addAttribute("speed", 10.0f);

    // Add background jobs
    player->addAttribute("backgroundJobs", std::vector<std::shared_ptr<Job>>({
        std::make_shared<PlayerControl>(input, world, *player)
    }));

    world.addEntity(std::move(player));
}

void GameObjectFactory::createHuman(World &world, glm::ivec2 position)
{
    auto human = std::make_unique<Entity>();

    // Add attributes
    human->addAttribute("position", position);
    human->addAttribute("thirst", (unsigned int)0);
    human->addAttribute("maxThirst", (unsigned int)10);
    human->addAttribute("renderableId", std::string("human"));
    human->addAttribute("perception", (unsigned int)10);
    human->addAttribute("timeSinceLastStep", (unsigned int)0);
    human->addAttribute("speed", 10.0f);

    // Add background jobs
    human->addAttribute("backgroundJobs", std::vector<std::shared_ptr<Job>>({
        std::make_shared<IncreaseThirst>(world, *human, 0.5f)
    }));

    // Add needs
    human->add(std::make_unique<Thirst>(world, *human));

    world.addEntity(std::move(human));
}

void GameObjectFactory::createWater(World &world, glm::ivec2 position)
{
    auto water = std::make_unique<GameObject>();

    // Add attributes
    water->addAttribute("position", position);
    water->addAttribute("renderableId", std::string("water"));
    water->addAttribute("thirstReduction", (unsigned int)10);
    water->addAttribute("consumable", true);

    // Add background jobs

    world.addObject(std::move(water));
}
// LCOV_EXCL_STOP
