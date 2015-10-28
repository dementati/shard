#pragma once

#include <gmock/gmock.h>

#include "../../src/logic/Entity.hpp"

class MockEntity : public Entity
{
public:
    MockEntity()
    : 
        Entity(std::string("")) 
    {}

    virtual void addNeed(std::unique_ptr<Need> need)
    {
        addNeedProxy(need.get());
    }
    MOCK_METHOD1(addNeedProxy, void(Need*));

    MOCK_METHOD0(selectNeed, Need&());

    MOCK_METHOD0(getPosition, glm::ivec2());

    MOCK_METHOD1(setPosition, void(glm::ivec2));

    MOCK_METHOD0(getRenderableId, const std::string());

    MOCK_CONST_METHOD0(unitName, const std::string());
};

template<class EntityType>
class MockEntityWrapper : public Entity 
{
    std::shared_ptr<EntityType> mEntity;

public:
    MockEntityWrapper()
    : 
        mEntity(std::make_shared<EntityType>())
    {
    }


    void add(CopyableNeed need) { return mEntity->add(need); }

    Need& selectNeed() { return mEntity->selectNeed(); }

    void setPosition(glm::ivec2 position) { mEntity->setPosition(position); }

    const std::string getRenderableId() { return mEntity->getRenderableId(); }

    const std::string unitName() const { return mEntity->unitName(); }

    EntityType& get()
    {
        return *mEntity;
    }
};
