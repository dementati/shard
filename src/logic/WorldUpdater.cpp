#include "WorldUpdater.hpp"

WorldUpdater::WorldUpdater(World &world)
: 
    mWorld(world)
{ 
}

void WorldUpdater::update(unsigned int dt)
{
    for(auto &object : mWorld.getObjects())
    {
        if(object->hasAttribute("backgroundJobs"))
        {
            for(auto &job : (*object)["backgroundJobs"].get<std::vector<std::shared_ptr<Job>>>())
            {
                job->execute(dt);
            }
        }
    }

    for(auto &entity : mWorld.getEntities())
    {
        if(entity->hasAttribute("backgroundJobs"))
        {
            for(auto &job : (*entity)["backgroundJobs"].get<std::vector<std::shared_ptr<Job>>>())
            {
                job->execute(dt);
            }
        } 

        Need& need = entity->selectNeed();
        need.execute(dt);
    }
}
