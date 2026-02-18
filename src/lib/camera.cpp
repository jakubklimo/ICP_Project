#include "camera.hpp"

Camera::Camera(float fov, float aspect, float nearPlane, float farPlane)
    : position(0.0f, 0.0f, 2.0f),
      front(0.0f, 0.0f, -1.0f),
      up(0.0f, 1.0f, 0.0f),
      fov(fov),
      aspect(aspect),
      nearPlane(nearPlane),
      farPlane(farPlane)
{}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}

void Camera::setAspect(float newAspect)
{
    aspect = newAspect;
}