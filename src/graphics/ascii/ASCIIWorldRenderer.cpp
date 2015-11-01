#include "ASCIIWorldRenderer.hpp"

ASCIIWorldRenderer::ASCIIWorldRenderer(RenderableStore<ASCIIRenderable> &store, World &world)
: 
    mRenderableStore(store), 
    mWorld(world)
{
}

void ASCIIWorldRenderer::render() const
{
    for(std::unique_ptr<Entity> &entityPtr : mWorld.getEntities())
    {
        Entity &entity = *entityPtr;
        ASSERT(entity.hasAttribute("renderableId"), "Entity lacks renderableId");
        ASSERT(entity.hasAttribute("position"), "Entity lacks position");

        ASCIIRenderable& renderable = 
            mRenderableStore.get(entity["renderableId"].get<std::string>());
        renderable.setPosition(entity["position"].get<glm::ivec2>());
        renderable.draw();
    }
}
