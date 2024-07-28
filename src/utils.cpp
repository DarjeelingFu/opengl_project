#include "utils.h"

std::vector<CallbackManager::KeyCallback> CallbackManager::keyCallbacks;
std::vector<CallbackManager::CursorPosCallback> CallbackManager::cursorPosCallbacks;

void CallbackManager::registerKeyCallback(KeyCallback callback) {
    keyCallbacks.push_back(callback);
}

void CallbackManager::registerCursorPosCallback(CursorPosCallback callback) {
    cursorPosCallbacks.push_back(callback);
}

void CallbackManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    for (const auto& callback : keyCallbacks) {
        callback(key, scancode, action, mods);
    }
}

void CallbackManager::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    for (const auto& callback : cursorPosCallbacks) {
        callback(xpos, ypos);
    }
}

void CallbackManager::registerFrameCallback(FrameCallback* callback) {
    frameCallbacks.push_back(callback);
}

void CallbackManager::callFrameCallbacks(GLFWwindow* window) {
    for (const auto& callback : frameCallbacks) {
        callback->onFrame(window);
    }
}

float Clock::currentTime;
float Clock::lastTime = 0.f;
float Clock::deltaTime = 0.f;
long long Clock::frameCnt = 0;
