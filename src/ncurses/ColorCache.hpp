#pragma once

#include <cassert>
#include <map>
#include <string>

#include "../core/Object.hpp"
#include "../utility/BitPattern.hpp"
#include "../utility/StreamLogger.hpp"

class ColorCache : public Object
{
    StreamLogger logger;

    std::map<uint64_t, short> colorIdMap;
    std::map<uint32_t, short> colorPairIdMap;

    short colorIdCounter;
    short colorPairIdCounter;

public:
    ColorCache();

    const std::string unitName() const;

    const short getColorId(const short r, const short g, const short b);

    const bool hasColorId(const short r, const short g, const short b);

    const short getColorPairId(const short colorId1, const short colorId2);

    const bool hasColorPairId(const short colorId1, const short colorId2);
};
