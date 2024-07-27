#ifndef ASSETS_H
#define ASSETS_H

#include <string>

class TestModel {
public:
    TestModel();
    void draw();

private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int texture;
};

class ShaderPipline {
public:
    unsigned int ID;

    ShaderPipline(const char* vertexPath, const char* fragmentPath);

    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 mat) const;

private:
    void checkCompileErrors(unsigned int shader, std::string type);
};

class Camera {
public:
    Camera(glm::vec3 position, float fov,  float width, float height);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    void setAspectRatio(float aspectRatio);
    void rotateView(float pitch, float yaw, float roll);

    void processKeyboard();
    void processMouseMovement(double xpos, double ypos);

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

#endif