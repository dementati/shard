#include "ASCIIWorldRenderer.hpp"

ASCIIWorldRenderer::ASCIIWorldRenderer(RenderableStore<ASCIIRenderable> &store, World &world)
: 
    mRenderableStore(store), 
    mWorld(world)
{
}

void ASCIIWorldRenderer::render() const
{
    for(std::unique_ptr<Entity> &entity : mWorld.getEntities())
    {
        ASCIIRenderable& renderable = mRenderableStore.get(entity->getRenderableId());
        renderable.setPosition(entity->getPosition());
        renderable.draw();
    }
}
