#pragma once

#include <glm/glm.hpp>

#include "../../input/InputSystem.hpp"
#include "../jobs/background/IncreaseThirst.hpp"
#include "../jobs/background/PlayerControl.hpp"
#include "../needs/Thirst.hpp"
#include "../Entity.hpp"
#include "../GameObject.hpp"
#include "../Need.hpp"
#include "../World.hpp"

class GameObjectFactory
{
public:
    static void createPlayer(World &world, InputSystem &input, glm::ivec2 position);

    static void createHuman(World &world, glm::ivec2 position);

    static void createWater(World &world, glm::ivec2 position);

    static void createRock(World &world, glm::ivec2 position);
};
