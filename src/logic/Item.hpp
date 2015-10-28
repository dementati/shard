#pragma once

#include <string>

#include "../core/Object.hpp"
#include "ItemType.hpp"

class Item : public Object
{
public:
    const std::string mRenderableId;
    const ItemType mType;

    Item(std::string renderableId, ItemType type);
};
