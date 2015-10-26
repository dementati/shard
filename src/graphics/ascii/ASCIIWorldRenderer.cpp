#include "ASCIIWorldRenderer.hpp"

ASCIIWorldRenderer::ASCIIWorldRenderer(RenderableStore<ASCIIRenderable> &store, World &world)
    : store(store), world(world)
{
}

void ASCIIWorldRenderer::render() const
{
    for(Entity &entity : world.getEntities())
    {
        ASCIIRenderable& renderable = store.get(entity.getRenderableId());
        renderable.setPosition(entity.getPosition());
        renderable.draw();
    }
}
