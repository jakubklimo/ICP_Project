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

void Object::update(float time)
{
    if (!animated)
        return;

    float t = time * animationSpeed + animationOffset;

    switch (animationType)
    {
        case 0: // levitace
        {
            float height = sin(t) * 0.5f;
            position = basePosition + glm::vec3(0, height, 0);
            break;
        }

        case 1: // rotace na místě
        {
            position = basePosition;
            rotation.y = t;
            break;
        }

        case 2: // kroužení
        {
            float radius = 1.0f;
            position = basePosition + glm::vec3(cos(t) * radius, 0, sin(t) * radius);
            rotation.y = t;
            break;
        }
    }
}

void Object::setAnimated(bool value)
{
    animated = value;
}

void Object::configureAnimation(int type, float offset, float speed)
{
    animated = true;
    animationType = type;
    animationOffset = offset;
    animationSpeed = speed;
}

void Object::setBasePosition(const glm::vec3& pos)
{
    basePosition = pos;
    position = pos;
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

void Object::setSoundId(int id)
{
    soundId = id;
}

int Object::getSoundId() const
{
    return soundId;
}

glm::vec3 Object::getPosition() const
{
    return position;
}