#include "assets.h"
#include "context.h"

class APP {
public:
    APP() :
    context {800, 600, "Hello World"},
    testModel {glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f))},
    worldAxis {},
    shaderPipline {"assets/shaders/vs.vs", "assets/shaders/fs.fs"},
    axisShader {"assets/shaders/axis.vs", "assets/shaders/axis.fs"},
    camera {glm::vec3(0.f, 0.f, 3.f), 60.f, 800.f, 600.f} {
        context.onCursorPos([this](double xpos, double ypos) { onCursorPos(xpos, ypos); });
        context.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    };

    void run() {
        while (!context.shouldClose()) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shaderPipline.use();
            shaderPipline.setMat4("view", camera.getViewMatrix());
            shaderPipline.setMat4("projection", camera.getProjectionMatrix());
            testModel.draw(shaderPipline);

            axisShader.use();
            axisShader.setMat4("view", camera.getViewMatrix());
            axisShader.setMat4("projection", camera.getProjectionMatrix());
            worldAxis.draw(axisShader);

            onFrame();

            context.pollEvents();
            context.swapBuffers();
        }
        context.terminate();
    }

    void onFrame() {
        glm::vec3 movement = glm::vec3(0.f, 0.f, 0.f);
        if(context.getKeyState(GLFW_KEY_W) == Context::PRESS) movement.x += 1.f;
        if(context.getKeyState(GLFW_KEY_S) == Context::PRESS) movement.x -= 1.f;
        if(context.getKeyState(GLFW_KEY_A) == Context::PRESS) movement.y -= 1.f;
        if(context.getKeyState(GLFW_KEY_D) == Context::PRESS) movement.y += 1.f;
        if(context.getKeyState(GLFW_KEY_SPACE) == Context::PRESS) movement.z += 1.f;
        if(context.getKeyState(GLFW_KEY_LEFT_SHIFT) == Context::PRESS) movement.z -= 1.f;
        if (movement != glm::vec3(0.f, 0.f, 0.f)) movement = glm::normalize(movement) * 0.03f;
        camera.movement(movement.x, movement.y, movement.z);
    }

    void onCursorPos(double xpos, double ypos) {
        static double lastX = xpos, lastY = ypos;
        double xoffset = xpos - lastX;
        double yoffset = ypos - lastY;
        lastX = xpos;
        lastY = ypos;
        float speed = 0.1f;

        camera.rotation(static_cast<float>(-yoffset) * speed, static_cast<float>(-xoffset) * speed, 0.f);
    }

private:
    Context context;
    TestModel testModel;
    WorldAxis worldAxis;

    ShaderPipline shaderPipline;
    ShaderPipline axisShader;
    Camera camera;
};

int main() {
    APP app;
    app.run();

    return 0;
}
