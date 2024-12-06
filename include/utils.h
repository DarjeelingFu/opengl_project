#ifndef UTILS_H
#define UTILS_H

#include "pch.h"
#include <vector>
#include <functional>
#include <chrono>

class Clocker {
public:
    Clocker();
    Clocker(int frameLimit);
    void start();
    void tick();
    float getDuration();
    void waitForFrame();
    void setFrameLimit(int limit);

private:
    int frameLimit;
    int frameDuration;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::microseconds duration;
};

#endif // UTILS_H