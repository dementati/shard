#pragma once

#include <functional>
#include <string>

#include "../../utility/math/Math.hpp"
#include "../Entity.hpp"
#include "../Job.hpp"
#include "../World.hpp"
#include "Move.hpp"
#include "Wander.hpp"

class FindWater : public Job
{
    World &mWorld;
    Entity &mOwner;
    RNG mRng;

public:
    FindWater(World &world, Entity &owner);

    virtual void execute(unsigned int dt);

    virtual GameObject* getClosestWaterInRange();

    virtual unsigned int getDistance(GameObject &object);

    virtual void consume(GameObject &water);
};
