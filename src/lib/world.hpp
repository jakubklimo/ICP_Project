#pragma once

#include <vector>

#include "object.hpp"
#include "mesh.hpp"
#include "camera.hpp"
#include "shader.hpp"

class Object;
class Camera;
class Shader;

class World {
    public:
        static void init();
        static void update(float delta);

        static const std::vector<Object*>& getObjects();
        static Camera* getCamera();
        static Shader* getShader();

    private:
        static std::vector<Object*> objects;
        static float elapsedTime;

        static Camera* camera;
        static Shader* shader;
};