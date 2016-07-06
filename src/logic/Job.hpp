#pragma once

#include <memory>

class Entity;

class Job
{
public:
    virtual ~Job() {};

    virtual void execute(unsigned int dt) = 0;
};

using JobStack = std::vector<std::shared_ptr<Job>>;
