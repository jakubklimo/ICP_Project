#include "world.hpp"

std::vector<Object*> World::objects;
float World::elapsedTime = 0.0f;

void World::init()
{
    Shader* shader = new Shader(
        "resources/shaders/vertex.glsl",
        "resources/shaders/fragment.glsl"
    );

    Texture* brick = new Texture("resources/textures/brick.png");
    Material* brickMaterial = new Material(shader, brick);

    Model* cube = new Model("resources/obj/cube.obj");

    Object* obj1 = new Object(cube, brickMaterial);
    obj1->setPosition(glm::vec3(-1.0f, 0.0f, 0.0f));

    Object* obj2 = new Object(cube, brickMaterial);
    obj2->setPosition(glm::vec3(1.0f, 0.0f, 0.0f));

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