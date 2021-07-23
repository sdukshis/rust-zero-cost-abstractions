#pragma once

#include <vector>
#include <random>
#include <iterator>
#include <tuple>
#include <numeric>

#include <range/v3/all.hpp>

#include "zip.hpp"

class TestSet
{
private:
    std::vector<std::vector<std::int32_t>> vectors;

public:
    template <class RandomDevice>
    TestSet(const size_t vec_length, const size_t num_vecs, RandomDevice &rng)
    {
        std::uniform_int_distribution<std::int32_t> uniform(0, 10);
        for (size_t i = 0; i < num_vecs; ++i)
        {
            std::vector<std::int32_t> v;
            v.reserve(vec_length);
            std::generate_n(std::back_inserter(v), vec_length, [&uniform, &rng]()
                            { return uniform(rng); });
            vectors.emplace_back(std::move(v));
        }
    }

    TestSet(const TestSet &other) = delete;
    TestSet(TestSet &&other) = default;
    TestSet &operator=(const TestSet &other) = delete;
    TestSet &operator=(TestSet &&other) = default;
    ~TestSet() = default;

    template <class RandomDevice>
    std::tuple<const std::vector<std::int32_t>&, const std::vector<std::int32_t>&> sample_pair(RandomDevice &rng) const
    {
        std::uniform_int_distribution<size_t> uniform(0, num_vecs() - 1);
        return {vectors[uniform(rng)], vectors[uniform(rng)]};
    }

    size_t num_vecs() const
    {
        return vectors.size();
    }

    size_t vec_length() const
    {
        return vectors.at(0).size();
    }
};

std::int64_t calculate_direct_index(const std::vector<std::int32_t> &a,
                                    const std::vector<std::int32_t> &b)
{

    assert(a.size() == b.size());
    const size_t len = a.size();
    std::int64_t res = 0;
    for (size_t i = 0; i < len; ++i)
    {
        if (a[i] > 2)
        {
            res += a[i] * b[i];
        }
    }
    return res;
}

std::int64_t calculate_direct(const std::vector<std::int32_t> &a,
                                    const std::vector<std::int32_t> &b)
{

    assert(a.size() == b.size());
    std::int64_t res = 0;

    for (const auto& [a, b] : zip(a, b)) {
        if (a > 2) {
            res += a * b;
        }
    }

    return res;
}

std::int64_t calculate_tranform_reduce(const std::vector<std::int32_t> &a,
                                        const std::vector<std::int32_t> &b)
{

    assert(a.size() == b.size());
    std::int64_t res = std::transform_reduce(a.begin(), a.end(), b.begin(), 0, std::plus<>(), [](std::int32_t a, std::int32_t b)
                                                { return (a > 2) ? a * b : 0; });

    return res;
}

std::int64_t calculate_ranges(const std::vector<std::int32_t> &a,
                                const std::vector<std::int32_t> &b)
{
    assert(a.size() == b.size());
    std::int64_t res = ranges::accumulate(ranges::views::zip(a, b)
        | ranges::views::filter([](auto &&values) { const auto& [a, b] = values; return a > 2; })
        | ranges::views::transform([](auto &&values) { const auto& [a, b] = values; return a * b; })
        , 0);

    return res;
}

std::int64_t calculate_avx(const std::vector<std::int32_t> &,
                            const std::vector<std::int32_t> &)
{
    assert(a.size() == b.size());

    std::int64_t res = 0;

    return res;
}
