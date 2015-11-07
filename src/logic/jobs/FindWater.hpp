#pragma once

#include <functional>
#include <memory>
#include <string>

#include "../../utility/math/Math.hpp"
#include "../../utility/LoggerFactory.hpp"
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
    std::unique_ptr<GameObjectUtils> mGameObjectUtils;

public:
    FindWater(World &world, Entity &owner);

    FindWater(World &world, Entity &owner, RNG &rng);

    virtual void execute(unsigned int dt);

    virtual GameObject* getClosestWaterInRange();

    virtual unsigned int getDistance(GameObject &object);

    virtual void consume(GameObject &water);
};
// LCOV_EXCL_STOP
