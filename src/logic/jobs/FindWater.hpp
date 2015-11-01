#pragma once

#include <functional>
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

    std::unique_ptr<Logger> mLogger;

    World &mWorld;
    Entity &mOwner;
    RNG &mRng;

public:
    FindWater(World &world, Entity &owner);

    FindWater(World &world, Entity &owner, RNG &rng);

    virtual void execute(unsigned int dt);

    virtual GameObject* getClosestWaterInRange();

    virtual unsigned int getDistance(GameObject &object);

    virtual void consume(GameObject &water);
};
// LCOV_EXCL_STOP
