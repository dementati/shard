#pragma once

#include <string>

#include "../core/Object.hpp"
#include "ItemType.hpp"

class Item : public Object
{
public:
    const std::string renderableId;
    const ItemType type;

    Item(std::string renderableId, ItemType type);
};
