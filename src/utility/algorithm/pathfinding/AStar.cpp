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

int AStar::dist(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

std::vector<glm::ivec2> AStar::findPath(glm::ivec2 startPosition, glm::ivec2 stopPosition,
    std::function<bool(glm::ivec2)> isBlocked, Box boundingBox)
{
    ASSERT(startPosition != stopPosition, "Start and stop positions cannot be the same");
    ASSERT(boundingBox.getVolume() > 1, 
        "Bounding box must have room for both a start and a stop position");
    ASSERT(boundingBox.contains(startPosition), "Bounding box must contain start position");
    ASSERT(boundingBox.contains(stopPosition), "Bounding box must contain stop position");

    std::unique_ptr<Logger> logger = LoggerFactory::createLogger("AStar", Severity::DEBUG);
    
    // Translate the search area to the positive quadrant originating at 0,0
    glm::ivec2 offset = -boundingBox.getPosition();
    startPosition = startPosition + offset;
    stopPosition = stopPosition + offset;

    std::function<glm::ivec2(int)> indexToVector = [&boundingBox](int i) {
        return glm::ivec2(i % boundingBox.getDimensions().x, i / boundingBox.getDimensions().x);
    };

    std::function<bool(int)> isBlockedInt = [&isBlocked, &indexToVector](int i) {
        return isBlocked(indexToVector(i));
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
    
    auto start = 0;
    x.push_back(startPosition.x);
    y.push_back(startPosition.y);
    index.push_back(y[start]*boundingBox.getDimensions().x + x[start]);
	g.push_back(0);
    f.push_back(dist(startPosition.x, startPosition.y, stopPosition.x, stopPosition.y));
    inOpen.push_back(true);
    closed.push_back(false);
    parent.push_back(start);

    auto target = 1;
    x.push_back(stopPosition.x);
    y.push_back(stopPosition.y);
    index.push_back(y[target]*boundingBox.getDimensions().x + x[target]);
    g.push_back(inf);
    f.push_back(0); 
    inOpen.push_back(false);
    closed.push_back(false);
    parent.push_back(-1);

	if(isBlockedInt(index[start]) || isBlockedInt(index[target]))
	   return std::vector<glm::ivec2>();	

	std::vector<int> open;
	open.push_back(start);
	std::make_heap(open.begin(), open.end(), PosFComp(f));

	std::unordered_map<int, int> neighbours;
	neighbours[index[start]] = start;

    bool targetReached = false;
	while(!open.empty()) 
	{
		auto current = open.front();

		if(index[current] == index[target]) 
		{
			target = current;
			targetReached = true;
			break;
		}

		std::pop_heap(open.begin(), open.end(), PosFComp(f));
		open.pop_back();
		inOpen[current] = false;
		closed[current] = true;

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
                    ASSERT(false, "This shouldn't happen");
                    break;
			}

			if(n_x < 0 
                || n_x >= (int)boundingBox.getDimensions().x 
                || n_y < 0 
                || n_y >= (int)boundingBox.getDimensions().y)
            {
				continue;
            }

			int n_i = n_y*boundingBox.getDimensions().x + n_x;
			if(isBlockedInt(n_i))
            {
				continue;
            }

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

			if(closed[neighbour])
				continue;

			int tentative_g = g[current] + 1;
			if(!inOpen[neighbour] || tentative_g < g[neighbour])
			{
                parent[neighbour] = current;
				g[neighbour] = tentative_g;
				f[neighbour] = g[neighbour] + dist(x[neighbour], y[neighbour], x[target], y[target]);
				if(!inOpen[neighbour]) 
				{
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


