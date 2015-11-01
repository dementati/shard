#include "GameObject.hpp"

GameObject::~GameObject()
{
}

Variant& GameObject::getAttribute(const std::string attributeId)
{
    return mAttributes[attributeId];
}

bool GameObject::hasAttribute(const std::string attributeId)
{
    return mAttributes.count(attributeId);
}

Variant& GameObject::operator[](const std::string attributeId)
{
    return getAttribute(attributeId);
}
