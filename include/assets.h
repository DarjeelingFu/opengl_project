#ifndef ASSETS_H
#define ASSETS_H

#include <string>
#include "utils.h"

class ShaderPipline {
public:
    unsigned int ID;

    ShaderPipline();
    ShaderPipline(const char* vertexPath, const char* fragmentPath);

    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 mat) const;

private:
    void checkCompileErrors(unsigned int shader, std::string type);
};

class TestModel {
public:
    TestModel();
    TestModel(glm::mat4 model);
    void draw(ShaderPipline &shader);
    void setModel(glm::mat4 model);

private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int texture;
    glm::mat4 model = glm::mat4(1.0f);
};

class WorldAxis {
public:
    WorldAxis();
    void draw(ShaderPipline &shader);

private:
    unsigned int VAO;
    unsigned int VBO;
};

class Camera {
public:
    Camera();
    Camera(glm::vec3 position, float fov,  float width, float height);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    glm::vec3 getPosition();
    void setAspectRatio(float aspectRatio);
    void rotation(float pitch, float yaw, float roll);
    void movement(float front, float right, float up);
    void setTarget(glm::vec3 target);

private:
    float aspectRatio;
    float fov;
    
    glm::vec3 position;

    glm::vec3 frontDefault;
    glm::vec3 upDefault;
    glm::vec3 rightDefault;
    
    float yaw = 0.f;
    float pitch = 0.f;
    float roll = 0.f;

    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

    float width;
    float height;
    float lastX;
    float lastY;
    bool firstMouse = true;
};

class Assets {
public:
    Assets();

    ShaderPipline shaderPipline;
    ShaderPipline axisShader;
    TestModel testModel;
    WorldAxis worldAxis;
    Camera camera;
};

#endif // ASSETS_H