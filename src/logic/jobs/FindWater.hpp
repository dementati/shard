#pragma once

#include <string>

#include "../Job.hpp"

class FindWater : public Job
{
    Need &need;

public:
    FindWater(Need &need);

    void execute(double dt);

    bool hasSucceeded();
};
