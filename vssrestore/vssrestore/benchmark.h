#pragma once
// Declaration of a latency benchmark class to measure the time taken for VSS snapshot restoration
#include <chrono>
#include <vector>
#include <string>
#include <iostream>

class LatencyBenchmark {
public:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = Clock::time_point;
    
    // To start the timer
    void start();
    // To stop the timer
    void stop();
    // To reset the timer
    void reset();
    // To display the time taken
    void report(const std::string& label = "Latency Benchmark") const;

private:
	// To keep track of the time and to note down max, min and average latencies
    TimePoint startTime;
    std::vector<long long> latencies;
};