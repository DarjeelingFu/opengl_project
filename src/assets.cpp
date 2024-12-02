#include <fstream>
#include <sstream>
#include <iostream>
#include "pch.h"
#include "assets.h"
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

TestModel::TestModel() {}

TestModel::TestModel(glm::mat4 model) : model(model) {
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    int width, height, nrChannels;
    unsigned char *data = stbi_load("assets/textures/container.jpg", &width, &height, &nrChannels, 0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
}

void TestModel::draw(ShaderPipline &shader) {
    shader.setMat4("model", model);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void TestModel::setModel(glm::mat4 model) {
    this->model = model;
}

ShaderPipline::ShaderPipline() {}

ShaderPipline::ShaderPipline(const char *vertexPath, const char *fragmentPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void ShaderPipline::use() { 
    glUseProgram(ID); 
}

void ShaderPipline::setBool(const std::string &name, bool value) const {         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void ShaderPipline::setInt(const std::string &name, int value) const { 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void ShaderPipline::setFloat(const std::string &name, float value) const { 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

void ShaderPipline::setMat4(const std::string &name, glm::mat4 mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderPipline::checkCompileErrors(unsigned int shader, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    }
}

Camera::Camera() {}

Camera::Camera(glm::vec3 position, float fov, float width, float height) {
    this->position = position;

    this->frontDefault = glm::vec3(0.0f, 0.0f, -1.0f);
    this->upDefault = glm::vec3(0.0f, 1.0f, 0.0f);
    this->rightDefault = glm::vec3(1.0f, 0.0f, 0.0f);

    this->front = this->frontDefault;
    this->up = this->upDefault;
    this->right = this->rightDefault;

    this->width = width;
    this->height = height;
    this->lastX = width / 2.0f;
    this->lastY = height / 2.0f;
    this->aspectRatio =  width / height;
    this->fov = fov;
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspective(glm::radians(fov), aspectRatio, 0.01f, 100.f);
}

glm::vec3 Camera::getPosition() { return this->position; }

void Camera::setAspectRatio(float aspectRatio) {
    this->aspectRatio = aspectRatio;
}

void Camera::rotation(float deltaPitch, float deltaYaw, float deltaRoll) {
    this->pitch += deltaPitch;
    this->yaw += deltaYaw;
    this->roll += deltaRoll;

    if(pitch > 89.0f) pitch = 89.0f;
    if(pitch < -89.0f) pitch = -89.0f;

    front = frontDefault;
    up = upDefault;
    right = rightDefault;
 
    glm::mat4 yaw_rotation = glm::rotate(glm::mat4(1.f), glm::radians(yaw), up);
    front = glm::normalize(yaw_rotation * glm::vec4(front, 1.0f));
    right = glm::normalize(glm::cross(front, up));

    glm::mat4 pitch_rotation = glm::rotate(glm::mat4(1.f), glm::radians(pitch), right);
    front = glm::normalize(pitch_rotation * glm::vec4(front, 1.0f));
    // up = glm::normalize(glm::cross(right, front));

    glm::mat4 roll_rotation = glm::rotate(glm::mat4(1.f), glm::radians(roll), front);
    up = glm::normalize(roll_rotation * glm::vec4(up, 1.0f));
    right = glm::normalize(glm::cross(front, up));
}

void Camera::movement(float front, float right, float up) {
    // position += front * this->front + right * this->right + up * this->up;
    glm::vec3 movement_front = glm::normalize(glm::vec3(this->front.x, 0.f, this->front.z));
    position += front * movement_front + right * this->right + up * this->up;
}

void Camera::setTarget(glm::vec3 target) {}

WorldAxis::WorldAxis() {
    float vertices[] = {
        0.f, 0.f, 0.f, 1.f, 0.f, 0.f,
        100.f, 0.f, 0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 0.f, 0.f, 1.f, 0.f,
        0.f, 100.f, 0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 0.f, 0.f, 1.f,
        0.f, 0.f, 100.f, 0.f, 0.f, 1.f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
}

void WorldAxis::draw(ShaderPipline &shader) {
    shader.setMat4("model", glm::mat4(1.0f));
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 6);
}

Transform::Transform() {
    position = glm::vec3(0.f, 0.f, 0.f);
    rotation = glm::vec3(0.f, 0.f, 0.f);
    scaling = glm::vec3(1.f, 1.f, 1.f);
}

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
    this->position = position;
    this->rotation = rotation;
    this->scaling = scale;
}

Transform::Transform(glm::vec3 position) : Transform() {
    this->position = position;
}

glm::vec3 Transform::getPosition() { return position; }

glm::vec3 Transform::getRotation() { return rotation; }

glm::vec3 Transform::getScale() { return scaling; }

void Transform::setPosition(glm::vec3 position) { this->position = position; }

void Transform::setRotation(glm::vec3 rotation) { this->rotation = rotation; }

void Transform::setScale(glm::vec3 scale) { this->scaling = scale; }

void Transform::translate(glm::vec3 translation) { this->position += translation; }

void Transform::rotate(glm::vec3 rotation) { this->rotation += rotation; }

void Transform::scale(glm::vec3 scaling) { this->scaling *= scaling; }

glm::mat4 Transform::getTransformMatrix() {
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scaling);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
    rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
    return translationMatrix * rotationMatrix * scaleMatrix;
}

void MyModel::loadFromFile(const char *path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    unsigned int numMeshes = scene->mNumMeshes;
    std::vector<std::vector<float>> meshes(numMeshes);
    std::vector<std::vector<unsigned int>> meshesIndices(numMeshes);

    for(unsigned int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[i];
        for(unsigned int j = 0; j < mesh->mNumVertices; j++) {
            meshes[i].push_back(mesh->mVertices[j].x);
            meshes[i].push_back(mesh->mVertices[j].y);
            meshes[i].push_back(mesh->mVertices[j].z);
        }
        for(unsigned int j = 0; j < mesh->mNumFaces; j++) {
            aiFace face = mesh->mFaces[j];
            for(unsigned int k = 0; k < face.mNumIndices; k++) {
                meshesIndices[i].push_back(face.mIndices[k]);
            }
        }
    }

    for(int i = 0; i < numMeshes; i++) {
        std::vector<float>& vertices = meshes[i];
        std::vector<unsigned int>& indices = meshesIndices[i];

        unsigned int VAO, VBO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
        nIndices.push_back(indices.size());

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        VAOs.push_back(VAO);
    }
}

MyModel::MyModel() {}

void MyModel::draw(ShaderPipline &shader) {
    for(unsigned int i = 0; i < VAOs.size(); i++) {
        shader.use();
        shader.setMat4("model", transform.getTransformMatrix());
        glBindVertexArray(VAOs[i]);
        glDrawElements(GL_TRIANGLES, nIndices[i], GL_UNSIGNED_INT, 0);
    }
}