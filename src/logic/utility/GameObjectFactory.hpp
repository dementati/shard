#pragma once

#include <glm/glm.hpp>

#include "../jobs/background/IncreaseThirst.hpp"
#include "../needs/Thirst.hpp"
#include "../Entity.hpp"
#include "../GameObject.hpp"
#include "../Need.hpp"
#include "../World.hpp"

class GameObjectFactory
{
public:
    static void createHuman(World &world, glm::ivec2 position);

    static void createWater(World &world, glm::ivec2 position);
};
