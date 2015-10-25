#pragma once

#include "../core/Object.hpp"

class Job : public Object
{
public:
    virtual void execute(double dt) = 0;

    virtual bool hasSucceeded() = 0;
};
