#include "context.h"
#include <iostream>

Context::KeyCallback Context::keyCallback;
Context::CursorPosCallback Context::cursorPosCallback;
Context::FrameBufferSizeCallback Context::frameBufferSizeCallback;

Context::Context(int windowWidth, int windowHeight, std::string windowTitle) : 
    windowWidth(windowWidth), 
    windowHeight(windowHeight), 
    windowTitle(windowTitle) {
        init();
        customInit();
        registerCallbacks();
}

int Context::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSwapInterval(1);

    return 0;
}

int Context::customInit() { 
    glViewport(0, 0, windowWidth, windowHeight);
    glEnable(GL_DEPTH_TEST);
    return 0; 
}

void Context::setInputMode(int mode, int value) {
    glfwSetInputMode(window, mode, value);
}

int Context::shouldClose() { return glfwWindowShouldClose(window); }

void Context::closeWindow() { glfwSetWindowShouldClose(window, true); }

void Context::pollEvents() { glfwPollEvents(); }

void Context::registerCallbacks() {
    glfwSetKeyCallback(window, Context::GLFWKeyCallback);
    glfwSetCursorPosCallback(window, Context::GLFWCursorPosCallback);
    glfwSetFramebufferSizeCallback(window, Context::GLFWFramebufferSizCallback);
}

void Context::swapBuffers() { glfwSwapBuffers(window); }

void Context::terminate() { 
    glfwTerminate(); 
}

void Context::GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(keyCallback) keyCallback(key, scancode, action, mods);
}

void Context::GLFWCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    if(cursorPosCallback) cursorPosCallback(xpos, ypos);
}

void Context::GLFWFramebufferSizCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    if(frameBufferSizeCallback) frameBufferSizeCallback(width, height);
}

void Context::onKey(KeyCallback callback) { keyCallback = callback; }

void Context::onCursorPos(CursorPosCallback callback) { cursorPosCallback = callback; }

void Context::onFrameBufferSize(FrameBufferSizeCallback callback) { frameBufferSizeCallback = callback; }

int Context::getKeyState(int key) {
    return static_cast<KeyState>(glfwGetKey(window, key));
}

int Context::getWindowWidth() { return this->windowWidth; }

int Context::getWindowHeight() { return this->windowHeight; }
