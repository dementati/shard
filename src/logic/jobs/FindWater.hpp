#pragma once

#include <functional>
#include <memory>
#include <string>

#include "../../utility/math/Math.hpp"
#include "../../utility/LoggerFactory.hpp"
#include "../utility/EntityUtils.hpp"
#include "../utility/GameObjectUtils.hpp"
#include "../Entity.hpp"
#include "../Job.hpp"
#include "../World.hpp"
#include "Move.hpp"
#include "Wander.hpp"

// LCOV_EXCL_START
class FindWater : public Job
{
    static RNG cTrueRng; 

    LoggerPtr mLogger;
    World &mWorld;
    Entity &mOwner;
    RNG &mRng;
    std::unique_ptr<EntityUtils> mEntityUtils;
    std::unique_ptr<GameObjectUtils> mGameObjectUtils;
    JobStack &mJobStack;

public:
    FindWater(JobStack& jobStack, World &world, Entity &owner);

    FindWater(JobStack& jobStack, World &world, Entity &owner, RNG &rng);

    virtual void execute(unsigned int dt);

    virtual unsigned int getDistance(GameObject &object);
};
// LCOV_EXCL_STOP
