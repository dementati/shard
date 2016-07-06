#pragma once

#include <memory>
#include <vector>

#include "Job.hpp"

class World;

class Need : public Job
{
public:
    virtual ~Need() {};

    virtual unsigned int getIntensity() = 0;

    virtual JobStack& getJobStack() = 0; 
};
