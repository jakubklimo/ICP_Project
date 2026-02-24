#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera {
    public:
        Camera(float fov, float aspect, float nearPlane, float farPlane);

        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix() const;

        void processKeyboard(GLFWwindow* window, float delta);
        void processMouse(float xoffset, float yoffset);
        void processScroll(float yoffset);

        void setAspect(float aspect);

        glm::vec3 getPosition() const;
        glm::vec3 getFront() const;

    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;

        float yaw;
        float pitch;

        float movementSpeed;
        float mouseSensitivity;
        float fov;

        float aspect;
        float nearPlane;
        float farPlane;

        void updateVectors();
};