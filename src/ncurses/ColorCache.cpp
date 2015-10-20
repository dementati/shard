#include "ColorCache.hpp"

ColorCache::ColorCache()
    : defaultLogger(*this), colorIdCounter(0), colorPairIdCounter(0)
{
}

const Logger& ColorCache::logger() const
{
    return defaultLogger;
}

const std::string ColorCache::unitName() const
{
    return "ColorCache";
}

const short ColorCache::getColorId(const short r, const short g, const short b)
{
    assert(sizeof(r) == 2 && "r must be a 16-bit integer");
    assert(sizeof(g) == 2 && "g must be a 16-bit integer");
    assert(sizeof(b) == 2 && "b must be a 16-bit integer");

    uint64_t hash = BitPattern::concatenate(r, g, b);
    if(colorIdMap.find(hash) == colorIdMap.end())
    {
        colorIdMap[hash] = colorIdCounter;
        colorIdCounter++;
    }

    return colorIdMap[hash];
}

const bool ColorCache::hasColorId(const short r, const short g, const short b)
{
    assert(sizeof(r) == 2 && "r must be a 16-bit integer");
    assert(sizeof(g) == 2 && "g must be a 16-bit integer");
    assert(sizeof(b) == 2 && "b must be a 16-bit integer");

    uint64_t hash = BitPattern::concatenate(r, g, b);
    return colorIdMap.find(hash) != colorIdMap.end();
}

const short ColorCache::getColorPairId(const short colorId1, const short colorId2)
{
    assert(sizeof(colorId1) == 2 && "colorId1 must be a 16-bit integer");
    assert(sizeof(colorId2) == 2 && "colorId2 must be a 16-bit integer");
    assert(colorId1 != colorId2 && "A pair must consist of distinct colors");

    uint32_t hash = BitPattern::concatenate(colorId1, colorId2);
    if(colorPairIdMap.find(hash) == colorPairIdMap.end())
    {
        colorPairIdMap[hash] = colorPairIdCounter;
        colorPairIdCounter++;
    }

    return colorPairIdMap[hash];
}

const bool ColorCache::hasColorPairId(const short colorId1, const short colorId2)
{
    assert(sizeof(colorId1) == 2 && "colorId1 must be a 16-bit integer");
    assert(sizeof(colorId2) == 2 && "colorId2 must be a 16-bit integer");
    assert(colorId1 != colorId2 && "A pair must consist of distinct colors");

    uint32_t hash = BitPattern::concatenate(colorId1, colorId2);
    return colorPairIdMap.find(hash) != colorPairIdMap.end();
}
