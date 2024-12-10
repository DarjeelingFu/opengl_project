#ifndef UTILS_H
#define UTILS_H

#include "pch.h"
#include <vector>
#include <functional>
#include <chrono>

class Clocker {
public:
    Clocker();
<<<<<<< HEAD
    Clocker(int fromeLimit);
    void start();
    void tick();
    float getDuration();
    void waitForFrame();

private:
    int frameLimit = -1;
    int frameDuration = -1;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::microseconds duration;
};

#endif // UTILS_H