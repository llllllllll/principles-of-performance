#include <benchmark/benchmark.h>

std::vector<double> make_array(std::size_t size) {
    std::vector<double> out(size);
    for (double& item : out) {
        item = std::rand();
    }
    return out;
}

template<typename T>
T sum(const std::vector<T>& arr, std::size_t stride) {
    T sum = 0;

    for (std::size_t ix = 0; ix < arr.size(); ix += stride) {
        sum += arr[ix];
    }

    return sum;
}

void bench_sum(benchmark::State& state) {
    auto arr = make_array(10000000);
    std::size_t stride = state.range(0);

    for (auto _ : state) {
        benchmark::DoNotOptimize(sum(arr, stride));
    }
}

BENCHMARK(bench_sum)->Apply([](benchmark::internal::Benchmark* b) {
    for (std::size_t n = 1; n < 64; ++n) {
        b->Arg(n);
    }
});
