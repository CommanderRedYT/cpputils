#pragma once

// system includes
#include <functional>
#include <vector>
#include <utility>

namespace cpputils {
template<typename... T>
class Signal
{
public:
    using Slot = std::function<void(T...)>;

    Signal &operator+=(Slot &&slot)
    {
        m_slots.emplace_back(std::move(slot));
        return *this;
    }

    Signal &operator+=(const Slot &slot)
    {
        m_slots.emplace_back(slot);
        return *this;
    }

    template<typename ...Targs>
    void operator()(Targs && ...args) const
    {
        for (const auto &slot : m_slots)
            slot(std::forward<Targs>(args)...);
    }

private:
    std::vector<Slot> m_slots;
};
} // namespace cpputils
