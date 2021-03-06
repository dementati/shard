#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "../utility/Assert.hpp"
#include "../utility/Variant.hpp"
#include "GameObject.hpp"
#include "Need.hpp"


// LCOV_EXCL_START
class Entity : public GameObject
{
    std::vector<std::unique_ptr<Need>> mNeeds;

public:
    Entity();

    virtual ~Entity();

    virtual void add(std::unique_ptr<Need> need);

    virtual Need& selectNeed();

    virtual bool hasNeeds();
};
// LCOV_EXCL_STOP
