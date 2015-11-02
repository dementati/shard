#include "ASCIIWorldRenderer.hpp"

ASCIIWorldRenderer::ASCIIWorldRenderer(ASCIIRenderingSystem &renderingSystem, RenderableStore<ASCIIRenderable> &store, World &world)
: 
    mRenderingSystem(renderingSystem),
    mRenderableStore(store), 
    mWorld(world)
{
}

void ASCIIWorldRenderer::render() const
{
    mRenderingSystem.clear();

    for(std::unique_ptr<GameObject> &objectPtr : mWorld.getObjects())
    {
        GameObject &object = *objectPtr;
        ASSERT(object.hasAttribute("renderableId"), "Object lacks renderableId");
        ASSERT(object.hasAttribute("position"), "Object lacks position");

        ASCIIRenderable& renderable = 
            mRenderableStore.get(object["renderableId"].get<std::string>());
        renderable.setPosition(object["position"].get<glm::ivec2>());
        renderable.draw();
    }

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

    mRenderingSystem.refresh();
}
