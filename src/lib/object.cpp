#include "object.hpp"

Object::Object(Model* model, Material* material) : model(model), material(material), position(0.0f), rotation(0.0f) {}

Object::Object(Mesh* mesh, Material* material) : mesh(mesh), material(material) {}

void Object::setPosition(const glm::vec3& pos)
{
    position = pos;
}

void Object::setRotation(const glm::vec3& rot)
{
    rotation = rot;
}

glm::mat4 Object::getModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);

    model = glm::rotate(model, rotation.x, glm::vec3(1,0,0));
    model = glm::rotate(model, rotation.y, glm::vec3(0,1,0));
    model = glm::rotate(model, rotation.z, glm::vec3(0,0,1));

    return model;
}

void Object::draw() const
{
    material->bind();
    if (model)
        model->draw();
    else if (mesh)
        mesh->draw();
}

Material* Object::getMaterial() const
{
    return material;
}