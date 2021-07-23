#pragma once

#include <tuple>

template <typename Iter1, typename Iter2>
class zip_iterator
{
private:
    using tuple = std::tuple<Iter1, Iter2>;

    tuple iters;

public:
    zip_iterator(Iter1 it1, Iter2 it2)
        : iters{it1, it2}
    {
    }

    zip_iterator(const zip_iterator &) = default;
    zip_iterator &operator=(const zip_iterator &) = default;

    auto operator*() { return std::tuple(*std::get<0>(iters),
                                         *std::get<1>(iters)); }

    zip_iterator &operator++()
    {
        ++std::get<0>(iters);
        ++std::get<1>(iters);
        return *this;
    }

    zip_iterator operator++(int)
    {
        zip_iterator prev{*this};
        ++(*this);
        return prev;
    }

    friend bool operator==(const zip_iterator &lhs, const zip_iterator &rhs)
    {
        return std::get<0>(lhs.iters) == std::get<0>(rhs.iters);
    }

    friend bool operator!=(const zip_iterator &lhs, const zip_iterator &rhs)
    {
        return std::get<0>(lhs.iters) != std::get<0>(rhs.iters);
    }
};

template <typename Container1, typename Container2>
class zip_container
{
private:
    Container1 &c1;
    Container2 &c2;

public:
    zip_container(Container1 &c1_, Container2 &c2_)
        : c1{c1_}, c2{c2_}
    {
    }

    auto begin() const
    {
        return zip_iterator{std::begin(c1), std::begin(c2)};
    }

    auto end() const
    {
        return zip_iterator{std::end(c1), std::end(c2)};
    }
};

template <typename Container1, typename Container2>
zip_container<Container1, Container2> zip(Container1 &c1, Container2 &c2)
{
    return zip_container{c1, c2};
}
