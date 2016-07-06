#pragma once

#include "Job.hpp"

class BackgroundJob : public Job
{
protected:
    JobStack mJobStack;
};
