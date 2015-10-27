#pragma once

#include <gmock/gmock.h>

#include "../../src/logic/Entity.hpp"

class MockEntity : public Entity
{
public:
    MockEntity()
        : Entity(std::string("")) {}

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
    std::shared_ptr<EntityType> wrappedEntity;

public:
    MockEntityWrapper()
        : wrappedEntity(std::make_shared<EntityType>())
    {
    }


    void add(CopyableNeed need) { return wrappedEntity->add(need); }

    Need& selectNeed() { return wrappedEntity->selectNeed(); }

    void setPosition(glm::ivec2 position) { wrappedEntity->setPosition(position); }

    const std::string getRenderableId() { return wrappedEntity->getRenderableId(); }

    const std::string unitName() const { return wrappedEntity->unitName(); }

    EntityType& get()
    {
        return *wrappedEntity;
    }
};
