#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class GUI {
    public:
        static void init(GLFWwindow* window);
        static void beginFrame();
        static void render();
        static void endFrame();
        static void shutdown();
};