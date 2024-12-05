#include "assets.h"
#include "context.h"
#include <vector>
#include <iostream>
#include "utils.h"

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
        context.onKey([this](int key, int scancode, int action, int mods) { onKey(key, scancode, action, mods); });
        context.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        xyz.loadFromFile("assets/xyz.obj");
        xyz.transform.scale(glm::vec3(0.2f, 0.2f, 0.2f));
    };

    void run() {
        while (!context.shouldClose()) {
            clocker.start();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shaderPipline.use();
            shaderPipline.setMat4("view", camera.getViewMatrix());
            shaderPipline.setMat4("projection", camera.getProjectionMatrix());
            testModel.draw(shaderPipline);
            for(auto& model : testModels) {
                model.draw(shaderPipline);
            }
            xyz.draw(shaderPipline);

            axisShader.use();
            axisShader.setMat4("view", camera.getViewMatrix());
            axisShader.setMat4("projection", camera.getProjectionMatrix());
            worldAxis.draw(axisShader);

            clocker.tick();
            update();

            context.pollEvents();
            context.swapBuffers();

        }
        context.terminate();
    }

    void update() {
        glm::vec3 movement = glm::vec3(0.f, 0.f, 0.f);
        float velocity = 10.0f;
        if(context.getKeyState(GLFW_KEY_W) == Context::PRESS) movement.x += 1.f;
        if(context.getKeyState(GLFW_KEY_S) == Context::PRESS) movement.x -= 1.f;
        if(context.getKeyState(GLFW_KEY_A) == Context::PRESS) movement.y -= 1.f;
        if(context.getKeyState(GLFW_KEY_D) == Context::PRESS) movement.y += 1.f;
        if(context.getKeyState(GLFW_KEY_SPACE) == Context::PRESS) movement.z += 1.f;
        if(context.getKeyState(GLFW_KEY_LEFT_SHIFT) == Context::PRESS) movement.z -= 1.f;
        if(movement != glm::vec3(0.f, 0.f, 0.f)) movement = glm::normalize(movement) * velocity * clocker.getDuration();
        camera.movement(movement.x, movement.y, movement.z);
        xyz.transform.setPosition(camera.getPosition() + camera.front * 4.f);
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

    void onKey(int key, int scancode, int action, int mods) {
        if(key == GLFW_KEY_E && action == GLFW_RELEASE) {
            std::cout << "Position: " << camera.getPosition().x << ", " << camera.getPosition().y << ", " << camera.getPosition().z << std::endl;
            testModels.push_back(TestModel(glm::translate(glm::mat4(1.0f), glm::vec3(camera.getPosition()))));
        }
        if(key == GLFW_KEY_R && action == GLFW_RELEASE) {
            testModels.clear();
        }
        if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
            context.closeWindow();
        }
    }

private:
    Context context;
    TestModel testModel;
    WorldAxis worldAxis;

    std::vector<TestModel> testModels;

    ShaderPipline shaderPipline;
    ShaderPipline axisShader;
    Camera camera;

    Clocker clocker;
    MyModel xyz;

    bool paused = false;

};

int main() {
    APP app;
    app.run();

    return 0;
}
