#pragma once

#include <gmock/gmock.h>

#include "../../src/logic/World.hpp"

class MockWorld : public World
{
public:
    MOCK_METHOD1(getAttribute, Variant&(std::string));

    MOCK_METHOD2(addAttribute, void(const std::string, Variant));

    MOCK_METHOD1(hasAttribute, bool(std::string));

    virtual Variant& operator[](const std::string attributeId) { return getAttribute(attributeId); };

    MOCK_METHOD0(getEntities, std::vector<std::unique_ptr<Entity>>&());

    virtual void addEntity(std::unique_ptr<Entity> entity)
    {
        addEntityProxy(entity.get());
    }
    MOCK_METHOD1(addEntityProxy, void(Entity*));

    MOCK_METHOD1(removeEntity, void(Entity&));

    MOCK_METHOD0(getObjects, std::vector<std::unique_ptr<GameObject>>&());

    virtual void addObject(std::unique_ptr<GameObject> object)
    {
        addObjectProxy(object.get());
    }
    MOCK_METHOD1(addObjectProxy, void(GameObject*));

    MOCK_METHOD1(removeObject, void(GameObject&));

    MOCK_METHOD2(setBlockedMapIfSolid, void(GameObject&, bool));

    MOCK_METHOD1(isBlocked, bool(glm::ivec2));
};
