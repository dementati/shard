#include "WorldUpdater.hpp"

WorldUpdater::WorldUpdater(World &world)
: 
    mWorld(world)
{ 
}

void WorldUpdater::update(double dt)
{
    for(std::unique_ptr<Entity>& entity : mWorld.getEntities())
    {
        Need& need = entity->selectNeed();
        Job& job = need.getJob();
        job.execute(dt);
    }
}
