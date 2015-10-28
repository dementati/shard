#pragma once

#include <cassert>
#include <map>
#include <string>

#include "../core/Object.hpp"
#include "../utility/BitPattern.hpp"
#include "../utility/StreamLogger.hpp"

// LCOV_EXCL_START
class ColorCache : public Object
{
    short mColorIdCounter;
    short mColorPairIdCounter;

    std::map<uint64_t, short> mColorIdMap;
    std::map<uint32_t, short> mColorPairIdMap;

    StreamLogger mLogger;


public:
    ColorCache();

    const std::string unitName() const;

    short getColorId(const short r, const short g, const short b);

    bool hasColorId(const short r, const short g, const short b);

    short getColorPairId(const short colorId1, const short colorId2);

    bool hasColorPairId(const short colorId1, const short colorId2);
};
// LCOV_EXCL_STOP
