#include "WorldUpdater.hpp"

WorldUpdater::WorldUpdater(World &world)
: 
    mWorld(world)
{ 
}

void WorldUpdater::update(unsigned int dt)
{
    for(std::unique_ptr<Entity>& entity : mWorld.getEntities())
    {
        Need& need = entity->selectNeed();
        need.execute(dt);
    }
}
