#pragma once

class Job
{
public:
    virtual ~Job() {};

    virtual void execute(unsigned int dt) = 0;
};
