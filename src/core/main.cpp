#include <chrono>

#include "../utility/LoggerFactory.hpp"
#include "Game.hpp"
#include "SimpleGame.hpp"

int main() 
{
    LoggerPtr logger(LoggerFactory::createLogger("main", Severity::DEBUG));

    logger->info("Initializing...");

    // Create game object
    SimpleGame simpleGame;
    Game *game = &simpleGame;

    uint64_t lastTime = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();

    // Start main loop
    logger->info("Starting main game loop");
    while(true) {
        // Compute delta time
        uint64_t currentTime = std::chrono::duration_cast< std::chrono::milliseconds >(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();

        unsigned int dt = (unsigned int)(currentTime - lastTime);

        if(dt > 0)
        {
            lastTime = currentTime;
        }

        logger->debug(std::string("Computed delta time: ") + glm::to_string(dt));

        // Call update method 
        game->update(dt);

        // Call render method
        game->render();
    }

    return 0;
}
