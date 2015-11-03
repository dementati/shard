#pragma once

#include <gmock/gmock.h>

#include "../../src/logic/Job.hpp"


class MockJob : public Job
{
public:
    MOCK_METHOD1(execute, void(unsigned int));
};
