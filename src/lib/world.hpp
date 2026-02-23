#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "object.hpp"
#include "mesh.hpp"
#include "material.hpp"
#include "texture.hpp"

class Object;

class World {
    public:
        static void init();
        static void update(float delta);

        static const std::vector<Object*>& getObjects();

    private:
        static std::vector<Object*> objects;
        static float elapsedTime;
};