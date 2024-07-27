#ifndef UTILS_H
#define UTILS_H

#include "pch.h"
#include <vector>
#include <functional>

class InputCallbackManager {
public:
    using KeyCallback = std::function<void(int key, int scancode, int action, int mods)>;
    using CursorPosCallback = std::function<void(double xpos, double ypos)>;

    static void registerKeyCallback(KeyCallback callback) {
        keyCallbacks.push_back(callback);
    }

    static void registerCursorPosCallback(CursorPosCallback callback) {
        cursorPosCallbacks.push_back(callback);
    }

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        for (const auto& callback : keyCallbacks) {
            callback(key, scancode, action, mods);
        }
    }

    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
        for (const auto& callback : cursorPosCallbacks) {
            callback(xpos, ypos);
        }
    }

private:
    static std::vector<KeyCallback> keyCallbacks;
    static std::vector<CursorPosCallback> cursorPosCallbacks;
};

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