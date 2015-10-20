#include "SimpleGame.hpp"


// LCOV_EXCL_START <- This method causes side effects that can't be tested automatically.
void SimpleGame::update(const double dt) 
{
    std::cout << "Update!" << std::endl;
}
// LCOV_EXCL_STOP

// LCOV_EXCL_START <- This method causes side effects that can't be tested automatically.
void SimpleGame::render() const 
{
    std::cout << "Render!" << std::endl;
}
// LCOV_EXCL_STOP
