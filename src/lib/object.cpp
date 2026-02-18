#include "object.hpp"

Object::Object(Mesh* mesh)
    : mesh(mesh),
      position(0.0f),
      rotation(0.0f),
      scale(1.0f)
{
}

void Object::setPosition(const glm::vec3& pos)
{
    position = pos;
}

void Object::setRotation(const glm::vec3& rot)
{
    rotation = rot;
}

void Object::setScale(const glm::vec3& s)
{
    scale = s;
}

glm::mat4 Object::getModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);

    model = glm::rotate(model, rotation.x, glm::vec3(1,0,0));
    model = glm::rotate(model, rotation.y, glm::vec3(0,1,0));
    model = glm::rotate(model, rotation.z, glm::vec3(0,0,1));

    model = glm::scale(model, scale);

    return model;
}

void Object::draw() const
{
    if (mesh)
        mesh->draw();
}