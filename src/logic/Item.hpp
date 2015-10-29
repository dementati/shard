#pragma once

#include <string>

#include "../core/Object.hpp"
#include "ItemType.hpp"

class Item : public Object
{
    const std::string mRenderableId;
    const ItemType mType;

public:
    Item(std::string renderableId, ItemType type);

    const std::string getRenderableId();

    const ItemType getType();
};
