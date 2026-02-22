#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <opencv2/opencv.hpp>

#include "shader.hpp"
#include "camera.hpp"
#include "mesh.hpp"
#include "object.hpp"
#include "world.hpp"
#include "gui.hpp"

class Renderer {
    public:
        static bool init();
        static void shutdown();

        static void beginFrame();
        static void endFrame();

        static void render();
        static void renderGUI();

        static bool shouldClose();
        static GLFWwindow* getWindow();

    private:
        static GLFWwindow* window;
};