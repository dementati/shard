#include "InvalidArgumentException.hpp"

// LCOV_EXCL_START
InvalidArgumentException::InvalidArgumentException(const std::string message)
    : StringException(message)
{
}
// LCOV_EXCL_STOP
