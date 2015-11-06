#pragma once

struct KeyHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

enum class Key
{
    None = -1,
    Up = 'w',
    Down = 's',
    Left = 'a',
    Right = 'd',
    Use = 'e',
    Quit = 'q'
};
