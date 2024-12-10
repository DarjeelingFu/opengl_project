#include "utils.h"
#include <iostream>

Clocker::Clocker() {
    startTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::microseconds(0);
    frameLimit = -1;
    frameDuration = -1;
}

Clocker::Clocker(int frameLimit) {
    startTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::microseconds(0);
    this->frameLimit = frameLimit;
    frameDuration = 1000000 / frameLimit;
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

void Clocker::waitForFrame() {
    if(frameLimit == -1) return;

    auto end = std::chrono::high_resolution_clock::now();
    auto thisDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - startTime);
    while(thisDuration.count() < frameDuration) {
        for(int i = 0; i < 1000; i++) {}
        end = std::chrono::high_resolution_clock::now();
        thisDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - startTime);
    }
}

void Clocker::setFrameLimit(int limit) { 
    frameLimit = limit; 
    frameDuration = 1000000 / frameLimit;
}
