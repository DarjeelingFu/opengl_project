#include "utils.h"

std::vector<InputCallbackManager::KeyCallback> InputCallbackManager::keyCallbacks;
std::vector<InputCallbackManager::CursorPosCallback> InputCallbackManager::cursorPosCallbacks;

float Clock::currentTime;
float Clock::lastTime = 0.f;
float Clock::deltaTime = 0.f;
long long Clock::frameCnt = 0;
