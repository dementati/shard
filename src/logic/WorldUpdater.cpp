#include "WorldUpdater.hpp"

WorldUpdater::WorldUpdater(World &world)
: 
    mLogger(LoggerFactory::createLogger("WorldUpdater", Severity::DEBUG)),
    mWorld(world)
{
    mLogger->info("Finished construction");
}

void WorldUpdater::update(unsigned int dt)
{
    mLogger->debug("Running object background jobs");
    mLogger->debug(std::string("Number of objects: ") + glm::to_string((int)mWorld.getObjects().size()));
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

    mLogger->debug("Updating entities");
    mLogger->debug(std::string("Number of entities: ") + glm::to_string((int)mWorld.getObjects().size()));
    for(auto &entity : mWorld.getEntities())
    {
        mLogger->debug("Running entity background jobs");
        if(entity->hasAttribute("backgroundJobs"))
        {
            for(auto &job : (*entity)["backgroundJobs"].get<std::vector<std::shared_ptr<Job>>>())
            {
                job->execute(dt);
            }
        } 
        else
        {
            mLogger->debug("No background jobs");
        }

        mLogger->debug("Selecting needs");
        Need& need = entity->selectNeed();
        need.execute(dt);
    }

    mWorld.removeDeadEntities();
}
