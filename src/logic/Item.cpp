#include "Item.hpp"

Item::Item(std::string renderableId, ItemType type)
: 
    mRenderableId(renderableId), 
    mType(type)
{    
}

const std::string Item::getRenderableId() const
{
    return mRenderableId;
}

const ItemType Item::getType() const
{
    return mType;
}
