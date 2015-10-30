#pragma once

#include <gmock/gmock.h>

#include "../../src/logic/Job.hpp"


class MockJob : public Job
{
public:
    MOCK_CONST_METHOD0(unitName, const std::string());

    MOCK_METHOD1(execute, void(double));

    MOCK_METHOD0(hasSucceeded, bool());
};
