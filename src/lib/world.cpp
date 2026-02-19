#include "world.hpp"

std::vector<Object*> World::objects;
float World::elapsedTime = 0.0f;

Camera *World::camera = nullptr;
Shader *World::shader = nullptr;

void World::init()
{
    camera = new Camera(45.0f, 800.0f/600.0f, 0.1f, 100.0f);

    shader = new Shader(
        "resources/shaders/vertex.glsl",
        "resources/shaders/fragment.glsl"
    );

    float vertices[] = {
        0.0f,  0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    Mesh* mesh = new Mesh(vertices, sizeof(vertices));

    Object* obj1 = new Object(mesh);
    obj1->setPosition(glm::vec3(-0.5f, 0.0f, 0.0f));

    Object* obj2 = new Object(mesh);
    obj2->setPosition(glm::vec3(0.5f, 0.0f, 0.0f));

    objects.push_back(obj1);
    objects.push_back(obj2);
}

void World::update(float delta)
{
    elapsedTime += delta;

    for (auto obj : objects)
        obj->setRotation(glm::vec3(0.0f, elapsedTime, 0.0f));
}

const std::vector<Object*>& World::getObjects()
{
    return objects;
}

Camera* World::getCamera()
{
    return camera;
}

Shader* World::getShader()
{
    return shader;
}