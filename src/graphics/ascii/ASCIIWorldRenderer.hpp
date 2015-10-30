#pragma once

#include "../../logic/World.hpp"
#include "../RenderableStore.hpp"
#include "ASCIIRenderable.hpp"

class ASCIIWorldRenderer
{
    RenderableStore<ASCIIRenderable> &mRenderableStore;
    World& mWorld;

public:
    ASCIIWorldRenderer(RenderableStore<ASCIIRenderable> &store, World& world);

    void render() const;
};
