#ifndef UTILS_H
#define UTILS_H

#include "pch.h"
#include <vector>
#include <functional>

class FrameCallback {
public:
    virtual void onFrame(GLFWwindow* window) = 0;
};

class CallbackManager {
public:
    using KeyCallback = std::function<void(int key, int scancode, int action, int mods)>;
    using CursorPosCallback = std::function<void(double xpos, double ypos)>;

    static void registerKeyCallback(KeyCallback callback);
    static void registerCursorPosCallback(CursorPosCallback callback);
    void registerFrameCallback(FrameCallback* callback);

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    void callFrameCallbacks(GLFWwindow* window);

private:
    static std::vector<KeyCallback> keyCallbacks;
    static std::vector<CursorPosCallback> cursorPosCallbacks;
    std::vector<FrameCallback*> frameCallbacks;
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