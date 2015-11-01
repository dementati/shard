#pragma once

#include "../../utility/math/geometry/Box.hpp"
#include "../GameObject.hpp"

class GameObjectUtils
{
public:
    static Box getPerceptionBox(GameObject &object);
};
