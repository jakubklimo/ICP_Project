#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "camera.hpp"
#include "mesh.hpp"
#include "object.hpp"
#include "world.hpp"

class Renderer {
    public:
        static bool init();
        static void shutdown();

        static void beginFrame();
        static void endFrame();

        static bool shouldClose();
        static GLFWwindow* getWindow();

    private:
        static GLFWwindow* window;
};