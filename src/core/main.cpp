/**
 * Contains main loop, spawns game object and calls its top-level methods.
 */

#include "game.hpp"
#include "simplegame.hpp"

int main(int argc, char *argv[]) 
{
    // Create game object
    SimpleGame simpleGame;
    Game *game = &simpleGame;

    // Start main loop
    while(true) {
        // Call update method 
        game->update(0.0);

        // Call render method
        game->render();
    }
}
