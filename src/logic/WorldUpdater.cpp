#include "WorldUpdater.hpp"

WorldUpdater::WorldUpdater(World &world)
: 
    mLogger(LoggerFactory::createLogger("WorldUpdater", Severity::DEBUG)),
    mWorld(world)
{
    LOG_INFO(mLogger, "Finished construction");
}

void WorldUpdater::update(unsigned int dt)
{
    LOG_DEBUG(mLogger, "Running object background jobs");
    LOG_DEBUG(mLogger, "Number of objects: " << mWorld.getObjects().size());
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

    LOG_DEBUG(mLogger, "Updating entities");
    LOG_DEBUG(mLogger, "Number of entities: " << mWorld.getObjects().size());
    for(auto &entity : mWorld.getEntities())
    {
        LOG_DEBUG(mLogger, "Running entity background jobs");
        if(entity->hasAttribute("backgroundJobStacks"))
        {
            for(auto &jobStack : (*entity)["backgroundJobStacks"].get<std::vector<std::shared_ptr<JobStack>>>())
            {
                if(!jobStack->empty()) 
                {
                    jobStack->back()->execute(dt);
                }
            }
        } 
        else
        {
            LOG_DEBUG(mLogger, "No background jobs");
        }

        if(entity->hasNeeds())
        {
            LOG_DEBUG(mLogger, "Selecting needs");
            Need& need = entity->selectNeed();
            if(need.getJobStack().empty())
            {
                need.execute(dt);
            }
            else
            {
                need.getJobStack().back()->execute(dt);
            }
        }
    }

    mWorld.removeDeadEntities();
}
