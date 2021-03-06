#include <chrono>

#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "../utility/LoggerFactory.hpp"
#include "Game.hpp"
#include "SimpleGame.hpp"

int main(int argc, char **argv) 
{
    LoggerPtr logger(LoggerFactory::createLogger("main", Severity::DEBUG));

    LOG_INFO(logger, "Initializing...");

    // Create game object
    SimpleGame simpleGame;
    Game *game = &simpleGame;

    uint64_t lastTime = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();

    // Start main loop
    LOG_INFO(logger, "Starting main game loop");
    while(game->isRunning()) {
        // Compute delta time
        uint64_t currentTime = std::chrono::duration_cast< std::chrono::milliseconds >(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();

        unsigned int dt = (unsigned int)(currentTime - lastTime);

        if(dt > 0)
        {
            lastTime = currentTime;
        }

        LOG_DEBUG(logger, "Computed delta time: " << dt);

        // Call update method 
        game->update(dt);

        // Call render method
        game->render();
    }

    return 0;
}
