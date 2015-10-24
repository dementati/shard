#pragma once

#include <map>
#include <memory>
#include <string>

#include "../core/Object.hpp"

template <class R>
class RenderableStore : public Object
{
    std::map<std::string, std::unique_ptr<R>> store;

public:
    void add(std::string key, std::unique_ptr<R> renderable);

    R& get(const std::string key);

    const std::string unitName() const;
};

template <class R>
void RenderableStore<R>::add(std::string key, std::unique_ptr<R> renderable)
{
    assert(renderable && "Renderable must not be null.");

    store[key] = std::move(renderable);
}

template <class R>
R& RenderableStore<R>::get(const std::string key)
{
    assert(store.find(key) != store.end() && "Key does not exist");

    return *(store[key]);
}

// LCOV_EXCL_START
template <class R>
const std::string RenderableStore<R>::unitName() const
{
    return std::string("RenderableStore");
}
// LCOV_EXCL_STOP
