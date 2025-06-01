#pragma once
#include <chrono>
#include <vector>
#include <string>
#include <iostream>
#include <limits>

class LatencyBenchmark {
public:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;

    void start();
    void stop();
    void reset();
    void report(const std::string& label = "Latency Benchmark") const;

private:
    TimePoint startTime;
    std::vector<long long> latencies;
};