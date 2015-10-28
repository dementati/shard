#pragma once

#include <map>
#include <memory>
#include <string>

// LCOV_EXCL_START
template <class R>
class RenderableStore
{
    std::map<std::string, std::unique_ptr<R>> mStore = std::map<std::string, std::unique_ptr<R>>();

public:
    virtual ~RenderableStore();

    virtual void add(std::string key, std::unique_ptr<R> renderable);

    virtual R& get(const std::string key);
};
// LCOV_EXCL_START

template <class R>
RenderableStore<R>::~RenderableStore()
{
}

template <class R>
void RenderableStore<R>::add(std::string key, std::unique_ptr<R> renderable)
{
    assert(renderable && "Renderable must not be null.");

    mStore[key] = std::move(renderable);
}

template <class R>
R& RenderableStore<R>::get(const std::string key)
{
    assert(mStore.find(key) != mStore.end() && "Key does not exist");

    return *(mStore[key]);
}
