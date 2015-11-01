#include "SimpleGame.hpp"

SimpleGame::SimpleGame()
:
    mNcurses(),
    mRenderingSystem(mNcurses),
    mWorldUpdater(mWorld),
    mRenderableStore(),
    mWorldRenderer(mRenderableStore, mWorld)
{
    mRenderableStore.add("human", 
        std::make_unique<ASCIISingleCharacterRenderable>(mRenderingSystem, '@'));
    mRenderableStore.add("water", 
        std::make_unique<ASCIISingleCharacterRenderable>(mRenderingSystem, '@'));

    GameObjectFactory::createHuman(mWorld, glm::ivec2(10, 10));
}

// LCOV_EXCL_START <- This method causes side effects that can't be tested automatically.
void SimpleGame::update(const unsigned int dt) 
{
    mWorldUpdater.update(dt);
}
// LCOV_EXCL_STOP

// LCOV_EXCL_START <- This method causes side effects that can't be tested automatically.
void SimpleGame::render() const 
{
    mWorldRenderer.render();
}
// LCOV_EXCL_STOP
