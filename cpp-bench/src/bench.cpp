#include <random>
#include <iostream>

#include <benchmark/benchmark.h>

#include "test_set.hpp"

const size_t vec_length = 20'000;
const size_t num_vecs = 100;

static void sample_pair(benchmark::State& state) {
    std::random_device rd;
    std::default_random_engine rng(rd());
    TestSet test_set(vec_length, num_vecs, rng);
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        benchmark::DoNotOptimize(test_set.sample_pair(rng));
        
    }
}
// Register the function as a benchmark
BENCHMARK(sample_pair);

static void calculate_direct_index(benchmark::State& state) {
    std::random_device rd;
    std::default_random_engine rng(rd());
    TestSet test_set(vec_length, num_vecs, rng);
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        const auto& [a, b] = test_set.sample_pair(rng);
        benchmark::DoNotOptimize(test_set.calculate_direct_index(a, b));
    }
}

BENCHMARK(calculate_direct_index);

static void calculate_for_range(benchmark::State& state) {
    std::random_device rd;
    std::default_random_engine rng(rd());
    TestSet test_set(vec_length, num_vecs, rng);
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        const auto& [a, b] = test_set.sample_pair(rng);
        benchmark::DoNotOptimize(test_set.calculate_for_range(a, b));
    }
}

BENCHMARK(calculate_for_range);

static void calculate_ranges(benchmark::State& state) {
    std::random_device rd;
    std::default_random_engine rng(rd());
    TestSet test_set(vec_length, num_vecs, rng);
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        const auto& [a, b] = test_set.sample_pair(rng);
        benchmark::DoNotOptimize(test_set.calculate_ranges(a, b));
    }
}

BENCHMARK(calculate_ranges);

static void calculate_tranform_reduce(benchmark::State& state) {
    std::random_device rd;
    std::default_random_engine rng(rd());
    TestSet test_set(vec_length, num_vecs, rng);
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        const auto& [a, b] = test_set.sample_pair(rng);
        benchmark::DoNotOptimize(test_set.calculate_tranform_reduce(a, b));
    }
}

BENCHMARK(calculate_tranform_reduce);

// Run the benchmark
BENCHMARK_MAIN();
