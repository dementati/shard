#pragma once

#include <memory>

#include "../utility/CopyablePolymorphic.hpp"
#include "Job.hpp"

class World;
class Entity;
class Need;

using CopyableNeed = CopyablePolymorphic<Need>;

class Need : public Job
{
public:
    virtual ~Need() {};

    virtual unsigned int getIntensity() = 0;
};
