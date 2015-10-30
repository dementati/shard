#pragma once

#include <gmock/gmock.h>

#include "../../src/graphics/RenderableStore.hpp"

template <class R>
class MockRenderableStore : public RenderableStore<R>
{
public:
    virtual void add(std::string key, std::unique_ptr<R> renderable)
    {
        addProxy(key, renderable.get());
    }
    MOCK_METHOD2_T(addProxy, void(std::string, R*));

    MOCK_METHOD1_T(get, R&(const std::string));

    MOCK_CONST_METHOD0_T(unitName, const std::string());
};
