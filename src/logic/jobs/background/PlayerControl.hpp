#pragma once

#include <string>

#include "../../../input/InputSystem.hpp"
#include "../../../utility/Assert.hpp"
#include "../../../utility/LoggerFactory.hpp"
#include "../../utility/EntityUtils.hpp"
#include "../../Entity.hpp"
#include "../../BackgroundJob.hpp"
#include "../../World.hpp"

// LCOV_EXCL_START
class PlayerControl : public BackgroundJob
{
    InputSystem &mInput;
    World &mWorld;
    Entity &mOwner;
    std::unique_ptr<EntityUtils> mEntityUtils;
    LoggerPtr mLogger;

public:
    PlayerControl(InputSystem &input, World &world, Entity &owner);

    PlayerControl(InputSystem &input, World &world, Entity &owner, std::unique_ptr<EntityUtils> entityUtils);

    virtual void execute(unsigned int dt);

    void synchronizeCamera();
};
// LCOV_EXCL_STOP
