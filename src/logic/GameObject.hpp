#pragma once

#include <unordered_map>

#include "../utility/Variant.hpp"

class GameObject 
{
    std::unordered_map<std::string, Variant> mAttributes;

public:
    virtual ~GameObject();

    virtual Variant& getAttribute(const std::string attributeId);

    virtual void addAttribute(const std::string key, Variant value);

    virtual bool hasAttribute(const std::string attributeId);

    virtual Variant& operator[](const std::string attributeId);
};
