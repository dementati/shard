#pragma once

#include "../core/Object.hpp"
#include "Job.hpp"

class World;
class Entity;

class Need : public Object
{
public:
    virtual int getIntensity() = 0;

    virtual Job& getJob() = 0;

    virtual World& getWorld() = 0;

    virtual Entity& getOwner() = 0;
};
