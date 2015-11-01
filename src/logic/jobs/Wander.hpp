#pragma once

#include <glm/glm.hpp>

#include "../../core/RNG.hpp"
#include "../Entity.hpp"
#include "../Job.hpp"
#include "../World.hpp"

class Wander : public Job
{
    World &mWorld;
    Entity &mOwner;
    RNG &mRng;

public:
    Wander(World &world, Entity &owner, RNG &rng);

    virtual void execute(unsigned int dt);

    virtual bool canMove(unsigned int dt);

    virtual std::shared_ptr<glm::ivec2> findTarget();
};
