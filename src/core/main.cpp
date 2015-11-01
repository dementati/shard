#include <chrono>

#include "Game.hpp"
#include "SimpleGame.hpp"

int main() 
{
    // Create game object
    SimpleGame simpleGame;
    Game *game = &simpleGame;

    uint64_t lastTime = std::chrono::duration_cast< std::chrono::milliseconds >(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();

    // Start main loop
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

        // Call update method 
        game->update(dt);

        // Call render method
        game->render();
    }

    return 0;
}
