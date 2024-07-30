#ifndef UTILS_H
#define UTILS_H

#include "pch.h"
#include <vector>
#include <functional>

class Clock {
public:
    static float currentTime;
    static float lastTime;
    static float deltaTime;

    static long long frameCnt;

    static void UpdateDeltaTime() {
        currentTime = static_cast<float>(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        frameCnt++;
    }
};

#endif // UTILS_H