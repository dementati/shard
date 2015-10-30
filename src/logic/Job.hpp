#pragma once

class Job
{
public:
    virtual ~Job() {};

    virtual void execute(double dt) = 0;

    virtual bool hasSucceeded() = 0;
};
