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
    player->addAttribute("thirst", (unsigned int)0);
    player->addAttribute("maxThirst", (unsigned int)10);
    player->addAttribute("isPlayer", true);

    // Add background jobs
    std::make_unique<PlayerControl>(input, world, *player);

    auto playerControl = std::make_shared<PlayerControl>(input, world, *player);
    auto jobStack = std::make_shared<JobStack>();
    jobStack->push_back(playerControl);

    player->addAttribute("backgroundJobStacks", 
        std::vector<std::shared_ptr<JobStack>>({ jobStack }));

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
    /*
    human->addAttribute("backgroundJobs", std::move(std::vector<std::unique_ptr<BackgroundJob>>({
        std::make_unique<IncreaseThirst>(world, *human, 0.5f) 
    }));
    */

    auto increaseThirst = std::make_shared<IncreaseThirst>(world, *human, 0.5f);
    auto jobStack = std::make_shared<JobStack>();
    jobStack->push_back(increaseThirst);

    human->addAttribute("backgroundJobStacks", 
        std::vector<std::shared_ptr<JobStack>>({ jobStack }));


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

void GameObjectFactory::createRock(World &world, glm::ivec2 position)
{
    auto rock = std::make_unique<GameObject>();

    // Add attributes
    rock->addAttribute("position", position);
    rock->addAttribute("renderableId", std::string("rock"));
    rock->addAttribute("solid", true);

    world.addObject(std::move(rock));
}
// LCOV_EXCL_STOP
