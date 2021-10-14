#pragma once

// system includes
#include <cstddef>
#include <iterator>

namespace cpputils {

//! TODO: replace this with std::span once we switch to C++20

template<typename _Tp>
struct ArrayView
{
    using value_type =             _Tp;
    using pointer =                value_type*;
    using const_pointer =          const value_type*;
    using reference =              value_type&;
    using const_reference =        const value_type&;
    using iterator =               value_type*;
    using const_iterator =         const value_type*;
    using size_type =              std::size_t;
    using difference_type =        std::ptrdiff_t;
    using reverse_iterator =       std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    constexpr ArrayView() noexcept = default;

    constexpr ArrayView(pointer begin, pointer end) noexcept :
        m_begin{begin}, m_end{end}
    {}

    constexpr ArrayView(pointer begin, std::size_t size) noexcept :
        m_begin{begin}, m_end{begin + size}
    {}

    constexpr ArrayView(const ArrayView &other) noexcept :
        m_begin{other.m_begin}, m_end{other.m_end}
    {}

    constexpr ArrayView(ArrayView &&other) noexcept :
        m_begin{std::move(other.m_begin)}, m_end{std::move(other.m_end)}
    {
        other.m_begin = {};
        other.m_end = {};
    }

    ArrayView &operator=(const ArrayView &other) noexcept
    {
        m_begin = other.m_begin;
        m_end = other.m_end;
        return *this;
    }

    ArrayView &operator=(ArrayView &&other) noexcept
    {
        m_begin = std::move(other.m_begin);
        other.m_begin = {};
        m_end = std::move(other.m_end);
        other.m_end = {};
        return *this;
    }

    bool operator==(const ArrayView &other) const noexcept
    {
        return m_begin == other.m_begin &&
               m_end == other.m_end;
    }

    // Iterators.
    constexpr iterator begin() noexcept
    { return iterator(data()); }

    constexpr const_iterator begin() const noexcept
    { return const_iterator(data()); }

    constexpr iterator end() noexcept
    { return iterator(data() + size()); }

    constexpr const_iterator end() const noexcept
    { return const_iterator(data() + size()); }

    constexpr reverse_iterator rbegin() noexcept
    { return reverse_iterator(end()); }

    constexpr const_reverse_iterator rbegin() const noexcept
    { return const_reverse_iterator(end()); }

    constexpr reverse_iterator rend() noexcept
    { return reverse_iterator(begin()); }

    constexpr const_reverse_iterator rend() const noexcept
    { return const_reverse_iterator(begin()); }

    constexpr const_iterator cbegin() const noexcept
    { return const_iterator(data()); }

    constexpr const_iterator cend() const noexcept
    { return const_iterator(data() + size()); }

    constexpr const_reverse_iterator crbegin() const noexcept
    { return const_reverse_iterator(end()); }

    constexpr const_reverse_iterator crend() const noexcept
    { return const_reverse_iterator(begin()); }

    // Capacity.
    constexpr size_type size() const noexcept { return std::distance(m_begin, m_end); }

    constexpr size_type max_size() const noexcept { return size(); }

    constexpr bool empty() const noexcept { return size() == 0; }

    // Element access.
    constexpr reference operator[](size_type __n) noexcept
    { return m_begin[__n]; }

    constexpr const_reference operator[](size_type __n) const noexcept
    { return m_begin[__n]; }

    constexpr reference at(size_type __n)
    {
        if (__n >= size())
          std::__throw_out_of_range_fmt(__N("array_view::at: __n (which is %zu) "
                            ">= size() (which is %zu)"),
                        __n, size());
        return m_begin[__n];
    }

    constexpr const_reference
    at(size_type __n) const
    {
        // Result of conditional expression must be an lvalue so use
        // boolean ? lvalue : (throw-expr, lvalue)
        return __n < size() ? m_begin[__n]
          : (std::__throw_out_of_range_fmt(__N("array_view::at: __n (which is %zu) "
                               ">= size() (which is %zu)"),
                           __n, size()),
             m_begin[0]);
    }

    constexpr reference front() noexcept
    { return *begin(); }

    constexpr const_reference front() const noexcept
    { return m_begin[0]; }

    constexpr reference back() noexcept
    { return size() ? *(end() - 1) : *end(); }

    constexpr const_reference back() const noexcept
    {
        return size() ? m_begin[size() - 1] : m_begin[0];
    }

    constexpr pointer data() noexcept
    { return m_begin; }

    constexpr const_pointer data() const noexcept
    { return m_begin; }

private:
    pointer m_begin{}, m_end{};
};

} // namespace cpputils
