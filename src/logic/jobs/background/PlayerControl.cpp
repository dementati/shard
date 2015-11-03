#include "PlayerControl.hpp"

PlayerControl::PlayerControl(InputSystem &input, World &world, Entity &player)
:
    mWorld(world),
    mPlayer(player),
    mInput(input)
{
    ASSERT(player.hasAttribute("position"), "Player must have a position");
    ASSERT(player["position"].isOfType<glm::ivec2>(), "Position must be a glm::ivec2");
    ASSERT(player.hasAttribute("timeSinceLastStep"), "Player must have timeSinceLastStep");
    ASSERT(player["timeSinceLastStep"].isOfType<unsigned int>(), "timeSinceLastStep must be an unsigned int");
    ASSERT(player.hasAttribute("speed"), "Player must have speed");
    ASSERT(player["speed"].isOfType<float>(), "speed must be a float");
}

void PlayerControl::execute(unsigned int dt)
{
    if(canMove(dt))
    {
        if(mInput.isPressed(Key::Up))
        {
            move(glm::ivec2(0, -1));
        }
        else if(mInput.isPressed(Key::Down))
        {
            move(glm::ivec2(0, 1));
        }
        else if(mInput.isPressed(Key::Left))
        {
            move(glm::ivec2(-1, 0));
        }
        else if(mInput.isPressed(Key::Right))
        {
            move(glm::ivec2(1, 0));
        }
    }
}

bool PlayerControl::canMove(unsigned int dt)
{
    unsigned int timeSinceLastStep = mPlayer["timeSinceLastStep"].get<unsigned int>() + dt;
    mPlayer["timeSinceLastStep"].set<unsigned int>(timeSinceLastStep);
    unsigned int stepLimit = (unsigned int)(1000.0f / mPlayer["speed"].get<float>());

    return timeSinceLastStep >= stepLimit;
}

void PlayerControl::move(glm::ivec2 deltaPosition)
{
    mPlayer["timeSinceLastStep"].set<unsigned int>(0);
    mPlayer["position"].set<glm::ivec2>(mPlayer["position"].get<glm::ivec2>() + deltaPosition);
}
