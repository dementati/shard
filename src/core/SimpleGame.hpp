#pragma once

#include <iostream>

#include <glm/glm.hpp>

#include "../graphics/ascii/sdl/SDLRenderingSystem.hpp"
#include "../graphics/ascii/ASCIISingleCharacterRenderable.hpp"
#include "../graphics/ascii/ASCIIRenderable.hpp"
#include "../graphics/ascii/ASCIIWorldRenderer.hpp"
#include "../graphics/RenderableStore.hpp"
#include "../input/SDLInputSystem.hpp"
#include "../logic/utility/GameObjectFactory.hpp"
#include "../logic/World.hpp"
#include "../logic/WorldUpdater.hpp"
#include "../sdl/SDLInterface.hpp"
#include "../utility/LoggerFactory.hpp"
#include "Game.hpp"
#include "RNG.hpp"

// LCOV_EXCL_START
class SimpleGame : public Game 
{
    LoggerPtr mLogger;

    RNG mRng;

    SDLInterface mSDL;
    SDLRenderingSystem mRenderingSystem;
    SDLInputSystem mInput;

    World mWorld;
    WorldUpdater mWorldUpdater;

    RenderableStore<ASCIIRenderable> mRenderableStore;
    ASCIIWorldRenderer mWorldRenderer;

    unsigned int mHumanSpawnTimer;
    unsigned int mWaterSpawnTimer;

public:
    SimpleGame();
    
    void update(const unsigned int dt);

    void render() const;

    bool isRunning();
};
// LCOV_EXCL_STOP
