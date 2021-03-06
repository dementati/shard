#include "AStar.hpp"

class PosFComp
{
    const std::vector<int>& mF;

public:
    PosFComp(const std::vector<int>& f) : mF(f) {}

    bool operator() (const int& i1, const int& i2) const
    {
        return mF[i1] > mF[i2];
    }
};

std::vector<glm::ivec2> AStar::findPath(glm::ivec2 startPosition, glm::ivec2 stopPosition,
    std::function<bool(glm::ivec2)> isBlocked, Box boundingBox)
{
    ASSERT(startPosition != stopPosition, "Start and stop positions cannot be the same");
    ASSERT(boundingBox.getVolume() > 1, "Bounding box must have room for both a start and a stop position");
    ASSERT(boundingBox.contains(startPosition), "Bounding box must contain start position");
    ASSERT(boundingBox.contains(stopPosition), "Bounding box must contain stop position");

    LoggerPtr logger = LoggerFactory::createLogger("AStar", Severity::DEBUG);
   
    LOG_DEBUG(logger, "startPosition = " << glm::to_string(startPosition));
    LOG_DEBUG(logger, "stopPosition = " << glm::to_string(stopPosition));

    // Translate the search area to the positive quadrant originating at 0,0
    glm::ivec2 offset = -boundingBox.getPosition();
    startPosition = startPosition + offset;
    stopPosition = stopPosition + offset;

    LOG_DEBUG(logger, "offset startPosition = " << glm::to_string(startPosition));
    LOG_DEBUG(logger, "offset stopPosition = " << glm::to_string(stopPosition));

    LOG_DEBUG(logger, "Initializing");

    LOG_DEBUG(logger, "Setting up lambdas");
    std::function<bool(glm::ivec2)> isBlockedOffset = [&] (glm::ivec2 p) {
        return isBlocked(p - offset);
    };

    std::function<glm::ivec2(int)> indexToVector = [&](int i) {
        return glm::ivec2(i % boundingBox.getDimensions().x, i / boundingBox.getDimensions().x);
    };

    std::function<bool(int)> isBlockedInt = [&](int i) {
        return isBlockedOffset(indexToVector(i));
    };

    int inf = std::numeric_limits<int>::max();

    std::vector<int> x;
    std::vector<int> y;
    std::vector<int> index;
    std::vector<int> g;
    std::vector<int> f;
    std::vector<bool> inOpen;
    std::vector<bool> closed;
    std::vector<int> parent;
    
    LOG_DEBUG(logger, "Initializing start position");
    auto start = 0;
    x.push_back(startPosition.x);
    y.push_back(startPosition.y);
    index.push_back(y[start]*boundingBox.getDimensions().x + x[start]);
    g.push_back(0);
    f.push_back(Math::manhattanDistance(startPosition, stopPosition));
    inOpen.push_back(true);
    closed.push_back(false);
    parent.push_back(start);

    LOG_DEBUG(logger, "Initializing target position");
    auto target = 1;
    x.push_back(stopPosition.x);
    y.push_back(stopPosition.y);
    index.push_back(y[target]*boundingBox.getDimensions().x + x[target]);
    g.push_back(inf);
    f.push_back(0); 
    inOpen.push_back(false);
    closed.push_back(false);
    parent.push_back(-1);

    LOG_DEBUG(logger, "Checking if start or target is blocked");
    if(isBlockedInt(index[start]) || isBlockedInt(index[target]))
    {
       LOG_DEBUG(logger, "Either start or target position is blocked");
       return std::vector<glm::ivec2>();    
    }

    LOG_DEBUG(logger, "Constructing open node heap");
    std::vector<int> open;
    open.push_back(start);
    std::make_heap(open.begin(), open.end(), PosFComp(f));

    LOG_DEBUG(logger, "Constructing neighbour map");
    std::unordered_map<int, int> neighbours;
    neighbours[index[start]] = start;

    LOG_DEBUG(logger, "Commencing main loop");

    bool targetReached = false;
    while(!open.empty()) 
    {
        // Select the position with the smallest F value from the sorted queue
        auto current = open.front();

        LOG_DEBUG(logger, "Current node = " << glm::to_string(indexToVector(index[current])));

        // If position is target, exit
        if(index[current] == index[target]) 
        {
            target = current;
            targetReached = true;
            break;
        }

        // Remove the position with the smallest F value from the queue
        std::pop_heap(open.begin(), open.end(), PosFComp(f));
        open.pop_back();
        inOpen[current] = false;
        closed[current] = true;

        // For each position up, down, left and right of the current position
        for(int i = 0; i < 4; i++) 
        {
            int n_x, n_y;
            switch(i)
            {
                case 0:
                    n_x = x[current];
                    n_y = y[current] - 1;
                    break;

                case 1:
                    n_x = x[current];
                    n_y = y[current] + 1;
                    break;

                case 2:
                    n_x = x[current] - 1;
                    n_y = y[current];
                    break;

                case 3:
                    n_x = x[current] + 1;
                    n_y = y[current];
                    break;

                default:
                    // LCOV_EXCL_START
                    ASSERT(false, "This shouldn't happen");
                    // LCOV_EXCL_STOP
                    break;
            }

            // If the neighbour is outside the bounding box, ignore it
            if(n_x < 0 
                || n_x >= (int)boundingBox.getDimensions().x 
                || n_y < 0 
                || n_y >= (int)boundingBox.getDimensions().y)
            {
                continue;
            }

            // If the neighbour is blocked by an obstacle, ignore it
            int n_i = n_y*boundingBox.getDimensions().x + n_x;
            if(isBlockedInt(n_i))
            {
                continue;
            }

            // If neighbour is not in neighbours map, account for it in all relevant buffers
            unsigned int neighbour;
            if(neighbours.find(n_i) == neighbours.end())
            {
                x.push_back(n_x);
                y.push_back(n_y);
                index.push_back(n_y*boundingBox.getDimensions().x + n_x);
                g.push_back(inf);
                f.push_back(0);
                inOpen.push_back(false);
                closed.push_back(false);
                parent.push_back(-1);
                neighbour = (unsigned int)x.size() - 1; 
                neighbours[n_i] = neighbour;
            } 
            else 
            {
                neighbour = neighbours[n_i];
            }

            // If neighbour has already been visited, ignore it
            if(closed[neighbour])
                continue;

            // If the best route to the neighbour is through the curre
            int tentative_g = g[current] + 1;
            if(!inOpen[neighbour] || tentative_g < g[neighbour])
            {
                parent[neighbour] = current;
                g[neighbour] = tentative_g;
                f[neighbour] = g[neighbour] + Math::manhattanDistance(x[neighbour], y[neighbour], x[target], y[target]);
                if(!inOpen[neighbour]) 
                {
                    LOG_DEBUG(logger, "Adding " << glm::to_string(indexToVector(index[neighbour])) << " to open queue");
                    open.push_back(neighbour);
                    std::push_heap(open.begin(), open.end(), PosFComp(f));
                    inOpen[neighbour] = true;
                } 
                else 
                {
                    std::make_heap(open.begin(), open.end(), PosFComp(f));
                }
            }
        }       
    }

    LOG_DEBUG(logger, "Main loop finished, constructing path or returning empty path");

    if(targetReached) 
    {
        std::vector<glm::ivec2> path;
        auto current = target;
        while(current != start) 
        {
            path.push_back(indexToVector(index[current]) - offset);
            current = parent[current];
        }
        path.push_back(indexToVector(index[start]) - offset);

        return path;
    } 
    else 
    {
        return std::vector<glm::ivec2>();
    }
}


