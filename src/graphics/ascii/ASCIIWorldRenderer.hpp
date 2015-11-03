#pragma once

#include "../../logic/World.hpp"
#include "../RenderableStore.hpp"
#include "ASCIIRenderable.hpp"
#include "ASCIIRenderingSystem.hpp"

class ASCIIWorldRenderer
{
    ASCIIRenderingSystem &mRenderingSystem;
    RenderableStore<ASCIIRenderable> &mRenderableStore;
    World& mWorld;

public:
    ASCIIWorldRenderer(ASCIIRenderingSystem &renderingSystem, RenderableStore<ASCIIRenderable> &store, World& world);

    void render() const;
};
