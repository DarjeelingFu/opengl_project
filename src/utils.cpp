#include "utils.h"
#include <iostream>

Clocker::Clocker() {
    startTime = std::chrono::high_resolution_clock::now();
    duration = std::chrono::microseconds(0);
}

Clocker::Clocker(int frameLimit){
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
    if(frameDuration != -1) {
        auto thisEnd = std::chrono::high_resolution_clock::now();
        auto thisDuration = std::chrono::duration_cast<std::chrono::microseconds>(thisEnd - startTime);
        
        while (thisDuration.count() < frameDuration) {
            int cnt = 0;
            while(cnt < 10000) cnt += 1;
            thisEnd = std::chrono::high_resolution_clock::now();
            thisDuration = std::chrono::duration_cast<std::chrono::microseconds>(thisEnd - startTime);
        }
    }
}
