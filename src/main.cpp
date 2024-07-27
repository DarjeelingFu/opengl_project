#include "pch.h"
#include <iostream>
#include "assets.h"
#include "utils.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow* window);

int width = 800, height = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Project", NULL, NULL);
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

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, InputCallbackManager::cursorPosCallback);
    
    glfwSetKeyCallback(window, InputCallbackManager::keyCallback);

    TestModel testModel = TestModel();
    ShaderPipline shaderPipline = ShaderPipline("assets/shaders/vs.vs", "assets/shaders/fs.fs");
    Camera camera = Camera(glm::vec3(0.f, 0.f, 3.f), 45.f, (float) width, (float) height);

    glm::mat4 model = glm::mat4(1.0f);

    while (!glfwWindowShouldClose(window)) {
        Clock::UpdateDeltaTime();

        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderPipline.use();
        shaderPipline.setMat4("model", model);
        shaderPipline.setMat4("view", camera.getViewMatrix());
        shaderPipline.setMat4("projection", camera.getProjectionMatrix());

        testModel.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
