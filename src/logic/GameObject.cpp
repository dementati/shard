#include "GameObject.hpp"

GameObject::~GameObject()
{
}

Variant& GameObject::getAttribute(const std::string attributeId)
{
    return mAttributes[attributeId];
}

void GameObject::addAttribute(const std::string key, Variant variant)
{
    mAttributes[key] = variant;
}

bool GameObject::hasAttribute(const std::string attributeId)
{
    return mAttributes.count(attributeId);
}

Variant& GameObject::operator[](const std::string attributeId)
{
    return getAttribute(attributeId);
}
