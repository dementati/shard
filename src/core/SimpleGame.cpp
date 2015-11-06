#include "SimpleGame.hpp"

// LCOV_EXCL_START <- This class is constantly in flux and it'll be tedious to rewrite
//                    the tests every time.
SimpleGame::SimpleGame()
:
    mLogger(LoggerFactory::createLogger("SimpleGame", Severity::DEBUG)),
    mRng(RNG::createTrueRandomRNG()),
    mSDL("Shard", glm::uvec2(640, 480)),
    mRenderingSystem(mSDL),
    mInput(mSDL),
    mWorldUpdater(mWorld),
    mRenderableStore(),
    mWorldRenderer(mRenderingSystem, mRenderableStore, mWorld),
    mHumanSpawnTimer(0),
    mWaterSpawnTimer(0)
{
    mRenderableStore.add("player", 
        std::make_unique<ASCIISingleCharacterRenderable>(mRenderingSystem, '@'));
    mRenderableStore.add("human", 
        std::make_unique<ASCIISingleCharacterRenderable>(mRenderingSystem, '&'));
    mRenderableStore.add("water", 
        std::make_unique<ASCIISingleCharacterRenderable>(mRenderingSystem, '~'));

   
    GameObjectFactory::createPlayer(mWorld, mInput, glm::ivec2(5, 5));

    for(int i = 0; i < 5; i++)
    {
        GameObjectFactory::createHuman(mWorld, mRng.random(glm::ivec2(0, 0), glm::ivec2(200, 50)));
    }

    for(int i = 0; i < 20; i++)
    {
        GameObjectFactory::createWater(mWorld, mRng.random(glm::ivec2(0, 0), glm::ivec2(200, 50)));
    }

    mLogger->info("Finished construction");
}

void SimpleGame::update(const unsigned int dt) 
{
    mLogger->debug("Updating...");
    ASSERT(dt != 12391239, "");
    mWorldUpdater.update(dt);
    mInput.update();

    mHumanSpawnTimer += dt;
    mWaterSpawnTimer += dt;
    if(mWaterSpawnTimer >= 2000)
    {
        GameObjectFactory::createWater(mWorld, mRng.random(glm::ivec2(0, 0), glm::ivec2(200, 50)));
        mWaterSpawnTimer = 0;
    }

    if(mHumanSpawnTimer >= 5000)
    {
        GameObjectFactory::createHuman(mWorld, mRng.random(glm::ivec2(0, 0), glm::ivec2(200, 50)));
        mHumanSpawnTimer = 0;
    }
}

void SimpleGame::render() const 
{
    mLogger->debug("Rendering...");
    mWorldRenderer.render();
}
// LCOV_EXCL_STOP
