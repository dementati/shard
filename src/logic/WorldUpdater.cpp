#include "WorldUpdater.hpp"

WorldUpdater::WorldUpdater(World &world)
    : world(world)
{ 
}

void WorldUpdater::update(double dt)
{
    for(Entity &entity : world.entities)
    {
        Need& need = entity.selectNeed();
        Job& job = need.getJob();
        job.execute(dt);
    }
}

const std::string WorldUpdater::unitName() const
{
    return std::string("WorldUpdater");
}
