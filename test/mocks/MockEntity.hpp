#pragma once

#include <gmock/gmock.h>

#include "../../src/logic/Entity.hpp"

class MockEntity : public Entity
{
public:
    MockEntity()
    : 
        Entity() 
    {}

    virtual void addNeed(std::unique_ptr<Need> need)
    {
        addNeedProxy(need.get());
    }
    MOCK_METHOD1(addNeedProxy, void(Need*));

    MOCK_METHOD0(selectNeed, Need&());

    MOCK_METHOD0(hasNeeds, bool());

    MOCK_METHOD1(hasAttribute, bool(std::string));

    MOCK_METHOD1(getAttribute, Variant&(std::string));

    MOCK_METHOD2(addAttribute, void(const std::string, Variant value));

    virtual Variant& operator[](const std::string attributeId) 
    { 
        return getAttribute(attributeId); 
    };
};
