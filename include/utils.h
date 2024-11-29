#ifndef UTILS_H
#define UTILS_H

#include "pch.h"
#include <vector>
#include <functional>
#include <chrono>

class Clocker {
public:
    Clocker();
    void start();
    void tick();
    float getDuration();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::microseconds duration;
};

#endif // UTILS_H