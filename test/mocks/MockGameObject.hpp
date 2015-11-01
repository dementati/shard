#pragma once

#include <gmock/gmock.h>

#include "../../src/logic/GameObject.hpp"

class MockGameObject : public GameObject 
{
public:
    MockGameObject()
    : 
        GameObject() 
    {}

    MOCK_METHOD1(getAttribute, Variant&(std::string));

    MOCK_METHOD2(addAttribute, void(const std::string, Variant));

    MOCK_METHOD1(hasAttribute, bool(std::string));

    virtual Variant& operator[](const std::string attributeId) { return getAttribute(attributeId); };
};
