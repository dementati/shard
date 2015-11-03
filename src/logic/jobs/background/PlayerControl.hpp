#pragma once

#include <string>

#include "../../../input/InputSystem.hpp"
#include "../../../utility/Assert.hpp"
#include "../../Entity.hpp"
#include "../../Job.hpp"
#include "../../World.hpp"

// LCOV_EXCL_START
class PlayerControl : public Job
{
    World &mWorld;
    Entity &mPlayer;
    InputSystem &mInput;

public:
    PlayerControl(InputSystem &input, World &world, Entity &player);

    virtual void execute(unsigned int dt);

    bool canMove(unsigned int dt);

    void move(glm::ivec2 deltaPosition);
};
// LCOV_EXCL_STOP
