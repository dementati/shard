#include "IncreaseThirst.hpp"

IncreaseThirst::IncreaseThirst(World &world, Entity &owner, float unitPerSecond)
:
    mWorld(world),
    mOwner(owner),
    mUnitPerSecond(unitPerSecond)
{
    ASSERT(owner.hasAttribute("thirst"), "Owner must have position attribute");
    ASSERT(owner["thirst"].isOfType<unsigned int>(), "Owner thirst must be an unsigned int");
    ASSERT(owner.hasAttribute("maxThirst"), "Owner must have maxThirst attribute");
    ASSERT(owner["maxThirst"].isOfType<unsigned int>(), "Owner maxThirst must be an unsigned int");
    ASSERT(unitPerSecond > 0, "unitPerSecond must be positive");
}

void IncreaseThirst::execute(unsigned int dt)
{
    if(!mOwner.hasAttribute("IncreaseThirst.timer"))
    {
        mOwner.addAttribute("IncreaseThirst.timer", (unsigned int)0);
    }

    auto timer = mOwner["IncreaseThirst.timer"].get<unsigned int>();
    timer += dt;

    if(timer >= (unsigned int)(1000.0f/mUnitPerSecond))
    {
        unsigned int wholeSeconds = (unsigned int)((float)timer/1000.0f);
        unsigned int thirstDelta = (unsigned int)(mUnitPerSecond * (float)wholeSeconds);
        mOwner["thirst"].set<unsigned int>(mOwner["thirst"].get<unsigned int>() + thirstDelta);
        unsigned int wholeMilliseconds = wholeSeconds * 1000;

        ASSERT(wholeMilliseconds <= timer, "This would cause timer to underflow");
        timer -= wholeMilliseconds;
    }

    mOwner["IncreaseThirst.timer"].set<unsigned int>(timer);

    if(mOwner["thirst"].get<unsigned int>() > mOwner["maxThirst"].get<unsigned int>())
    {
        mOwner.addAttribute("dead", true);

        if(mOwner.hasAttribute("isPlayer"))
        {
            ASSERT(mOwner["isPlayer"].isOfType<bool>(), "isPlayer flag must be a bool");

            if(mOwner["isPlayer"].get<bool>())
            {
                ASSERT(mWorld.hasAttribute("running"), "World must have running flag");
                ASSERT(mWorld["running"].isOfType<bool>(), "Running flag must be a bool");

                mWorld["running"].set<bool>(false);
            }
        }
    }
}
