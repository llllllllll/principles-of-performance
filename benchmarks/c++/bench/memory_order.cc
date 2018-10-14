#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

#include <benchmark/benchmark.h>

constexpr std::size_t size = 1000000;
using type = std::int64_t;

void bench_random_access(benchmark::State& state) {
    std::vector<type> values(size);
    std::iota(values.begin(), values.end(), 0);

    std::vector<type> indices = values;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g);

    for (auto _ : state) {
        for (const type ix : indices) {
            benchmark::DoNotOptimize(values[ix]);
        }
    }
}
BENCHMARK(bench_random_access);


void bench_forward_linear_access(benchmark::State& state) {
    std::vector<type> values(size);
    std::iota(values.begin(), values.end(), 0);

    std::vector<type> indices = values;

    for (auto _ : state) {
        for (const type ix : indices) {
            benchmark::DoNotOptimize(values[ix]);
        }
    }
}
BENCHMARK(bench_forward_linear_access);


void bench_reverse_linear_access(benchmark::State& state) {
    std::vector<type> values(size);
    std::iota(values.begin(), values.end(), 0);

    std::vector<type> indices(values.rbegin(), values.rend());

    for (auto _ : state) {
        for (const type ix : indices) {
            benchmark::DoNotOptimize(values[ix]);
        }
    }
}
BENCHMARK(bench_reverse_linear_access);
