#ifndef ASSETS_H
#define ASSETS_H

#include <string>
#include "utils.h"
#include <vector>

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

    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

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

class Transform {
public:
    Transform();
    Transform(glm::vec3 position);
    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getScale();

    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);
    void setScale(glm::vec3 scale);

    void translate(glm::vec3 translation);
    void rotate(glm::vec3 rotation);
    void scale(glm::vec3 scaling);

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scaling;

    glm::mat4 getTransformMatrix();

    private:
};

class MyModel {
public:
    MyModel();
    Transform transform;
    void draw(ShaderPipline &shader);
    void loadFromFile(const char* path);

private:
    glm::mat4 transformMatrix;
    std::vector<unsigned int> VAOs;
    std::vector<unsigned int> nIndices;
};

#endif // ASSETS_H