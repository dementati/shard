#pragma once

#include "../../utility/math/geometry/Box.hpp"
#include "../GameObject.hpp"

class GameObjectUtils
{
public:
    virtual ~GameObjectUtils();

    virtual Box getPerceptionBox(GameObject &object);
};
