#pragma once

#include <string>

#include "../../../input/InputSystem.hpp"
#include "../../../utility/Assert.hpp"
#include "../../utility/EntityUtils.hpp"
#include "../../Entity.hpp"
#include "../../Job.hpp"
#include "../../World.hpp"

// LCOV_EXCL_START
class PlayerControl : public Job
{
    InputSystem &mInput;
    World &mWorld;
    Entity &mOwner;
    std::unique_ptr<EntityUtils> mEntityUtils;

public:
    PlayerControl(InputSystem &input, World &world, Entity &owner);

    PlayerControl(InputSystem &input, World &world, Entity &owner, std::unique_ptr<EntityUtils> entityUtils);

    virtual void execute(unsigned int dt);

    void synchronizeCamera();
};
// LCOV_EXCL_STOP
