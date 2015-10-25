#include "ASCIIWorldRenderer.hpp"

ASCIIWorldRenderer::ASCIIWorldRenderer(RenderableStore<ASCIIRenderable> &store, World &world)
    : store(store), world(world)
{
}

void ASCIIWorldRenderer::render() const
{
    for(Entity &entity : world.entities)
    {
        ASCIIRenderable& renderable = store.get(entity.renderableId);
        renderable.setPosition(entity.position);
        renderable.draw();
    }
}
