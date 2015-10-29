#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "../utility/Assert.hpp"
#include "../utility/Variant.hpp"
#include "Need.hpp"


// LCOV_EXCL_START
class Entity
{
    std::vector<CopyableNeed> mNeeds;
    glm::ivec2 mPosition;
    const std::string mRenderableId;
    std::map<std::string, Variant> mAttributes;

public:
    Entity(const std::string renderableId);

    virtual ~Entity();

    virtual void add(CopyableNeed need);

    virtual Need& selectNeed();

    virtual glm::ivec2 getPosition();

    virtual void setPosition(glm::ivec2 position);

    virtual const std::string getRenderableId();
};
// LCOV_EXCL_STOP
