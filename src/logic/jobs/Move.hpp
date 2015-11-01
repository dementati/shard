#pragma once

#include <glm/glm.hpp>

#include "../../utility/algorithm/Pathfinding.hpp"
#include "../Entity.hpp"
#include "../Job.hpp"
#include "../World.hpp"

// LCOV_EXCL_START
class Move : public Job
{
    World &mWorld;
    Entity &mOwner;
    glm::ivec2 mTarget;

public:
    Move(World &world, Entity &owner, glm::ivec2 target);

    virtual void execute(unsigned int dt);

    virtual bool isBlocked(glm::ivec2 position);

    virtual Box getPerceptionBox();

    virtual unsigned int getStepCount(unsigned int dt);
};
// LCOV_EXCL_STOP
