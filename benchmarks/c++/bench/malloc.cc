#include <cstdlib>

#include <benchmark/benchmark.h>

constexpr std::size_t size = 1000000;
using type = std::int64_t;

void bench_malloc(benchmark::State& state) {
    std::size_t size = state.range(0);
    std::vector<void*> ptrs(1 << 30);
    std::size_t ix = 0;

    for (auto _ : state) {
        void* p = std::malloc(size);
        benchmark::DoNotOptimize(p);
        state.PauseTiming();
        if (ix == ptrs.size()) {
            for (void* p : ptrs) {
                std::free(p);
            }
            ix = 0;
        }
        ptrs[ix++] = p;
        state.ResumeTiming();
    }
}
BENCHMARK(bench_malloc)->Range(64, 8096);
