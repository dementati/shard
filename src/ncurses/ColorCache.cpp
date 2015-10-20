#include "ColorCache.hpp"

ColorCache::ColorCache()
    : defaultLogger(*this), colorIdCounter(0)
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
    assert(sizeof(r) == 2);
    assert(sizeof(g) == 2);
    assert(sizeof(b) == 2);

    uint64_t hash = BitPattern::concatenate(r, g, b);
    if(colorIdMap.find(hash) == colorIdMap.end())
    {
        colorIdMap[hash] = colorIdCounter;
        colorIdCounter++;
    }

    return colorIdMap[hash];
}
