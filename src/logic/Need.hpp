#pragma once

#include <memory>

#include "../utility/CopyablePolymorphic.hpp"
#include "Job.hpp"

class World;
class Entity;
class Need;

using CopyableNeed = CopyablePolymorphic<Need>;

class Need
{
public:
    virtual ~Need() {};

    virtual int getIntensity() = 0;

    virtual Job& getJob() = 0;

    virtual World& getWorld() = 0;

    virtual Entity& getOwner() = 0;
};
