#include "ColorCache.hpp"

ColorCache::ColorCache()
: 
    mColorIdCounter(0), 
    mColorPairIdCounter(0),
    mColorIdMap(std::map<uint64_t, short>()),
    mColorPairIdMap(std::map<uint32_t, short>()),
    mLogger(LoggerFactory::createLogger("ColorCache", Severity::DEBUG))
{
}

short ColorCache::getColorId(const short r, const short g, const short b)
{
    ASSERT(sizeof(r) == 2, "r must be a 16-bit integer");
    ASSERT(sizeof(g) == 2, "g must be a 16-bit integer");
    ASSERT(sizeof(b) == 2, "b must be a 16-bit integer");

    uint64_t hash = BitPattern::concatenate(r, g, b);
    if(mColorIdMap.find(hash) == mColorIdMap.end())
    {
        mColorIdMap[hash] = mColorIdCounter;
        mColorIdCounter++;
    }

    return mColorIdMap[hash];
}

bool ColorCache::hasColorId(const short r, const short g, const short b)
{
    ASSERT(sizeof(r) == 2, "r must be a 16-bit integer");
    ASSERT(sizeof(g) == 2, "g must be a 16-bit integer");
    ASSERT(sizeof(b) == 2, "b must be a 16-bit integer");

    uint64_t hash = BitPattern::concatenate(r, g, b);
    return mColorIdMap.find(hash) != mColorIdMap.end();
}

short ColorCache::getColorPairId(const short colorId1, const short colorId2)
{
    ASSERT(sizeof(colorId1) == 2, "colorId1 must be a 16-bit integer");
    ASSERT(sizeof(colorId2) == 2, "colorId2 must be a 16-bit integer");
    ASSERT(colorId1 != colorId2, "A pair must consist of distinct colors");

    uint32_t hash = BitPattern::concatenate(colorId1, colorId2);
    if(mColorPairIdMap.find(hash) == mColorPairIdMap.end())
    {
        mColorPairIdMap[hash] = mColorPairIdCounter;
        mColorPairIdCounter++;
    }

    return mColorPairIdMap[hash];
}

bool ColorCache::hasColorPairId(const short colorId1, const short colorId2)
{
    ASSERT(sizeof(colorId1) == 2, "colorId1 must be a 16-bit integer");
    ASSERT(sizeof(colorId2) == 2, "colorId2 must be a 16-bit integer");
    ASSERT(colorId1 != colorId2, "A pair must consist of distinct colors");

    uint32_t hash = BitPattern::concatenate(colorId1, colorId2);
    return mColorPairIdMap.find(hash) != mColorPairIdMap.end();
}
