#ifndef CONTEXT_H
#define CONTEXT_H

#include "pch.h"
#include <string>
#include <functional>

class Context {
public:
    enum KeyState {
        RELEASE = GLFW_RELEASE,
        PRESS = GLFW_PRESS,
        REPEAT = GLFW_REPEAT
    };

    Context(int windowWidth, int windowHeight, std::string windowTitle);

    /// @brief initializations including GLFW and GLAD
    int init();
    /// @brief temporally used for custom initializations
    int customInit();
    void registerCallbacks();
    void setInputMode(int mode, int value);
    int shouldClose();
    void pollEvents();
    void terminate();
    void swapBuffers();

    static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void GLFWCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void GLFWFramebufferSizCallback(GLFWwindow* window, int width, int height);

    using KeyCallback = std::function<void(int key, int scancode, int action, int mods)>;
    using CursorPosCallback = std::function<void(double xpos, double ypos)>;
    using FrameBufferSizeCallback = std::function<void(int width, int height)>;
    
    static KeyCallback keyCallback;
    static CursorPosCallback cursorPosCallback;
    static FrameBufferSizeCallback frameBufferSizeCallback;

    void onKey(KeyCallback callback);
    void onCursorPos(CursorPosCallback callback);
    void onFrameBufferSize(FrameBufferSizeCallback callback);

    int getKeyState(int key);

private:
    int windowWidth = 800, windowHeight = 600;
    std::string windowTitle;
    GLFWwindow* window;
};

#endif // CONTEXT_H