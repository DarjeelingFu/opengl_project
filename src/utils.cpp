#include "utils.h"
#include <iostream>

Clocker::Clocker() {
    startTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::microseconds(0);
}

void Clocker::start() {
    startTime = std::chrono::high_resolution_clock::now();
}

void Clocker::tick() {
    auto end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - startTime);
}

float Clocker::getDuration() {
    return duration.count() / 1000000.0;
}