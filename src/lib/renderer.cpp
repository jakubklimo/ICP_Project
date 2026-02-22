#include "renderer.hpp"
#include <iostream>

GLFWwindow* Renderer::window = nullptr;

static bool firstMouse = true;
static float lastX = 400, lastY = 300;

static bool isFullscreen = false;
static bool vsyncEnabled = true;

static int savedPosX = 0;
static int savedPosY = 0;
static int savedWidth = 800;
static int savedHeight = 600;

static void toggleFullscreen(GLFWwindow* window)
{
    isFullscreen = !isFullscreen;

    if (isFullscreen)
    {
        glfwGetWindowPos(window, &savedPosX, &savedPosY);
        glfwGetWindowSize(window, &savedWidth, &savedHeight);

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwSetWindowMonitor(
            window,
            monitor,
            0,
            0,
            mode->width,
            mode->height,
            mode->refreshRate
        );
    }
    else
    {
        glfwSetWindowMonitor(
            window,
            nullptr,
            savedPosX,
            savedPosY,
            savedWidth,
            savedHeight,
            0
        );
    }

    firstMouse = true;
}

static void toggleVSync()
{
    vsyncEnabled = !vsyncEnabled;
    glfwSwapInterval(vsyncEnabled ? 1 : 0);

    std::cout << "VSync: " 
              << (vsyncEnabled ? "ON" : "OFF") 
              << std::endl;
}

static void takeScreenshot(GLFWwindow* window){
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    cv::Mat pixels(height, width, CV_8UC3);

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, pixels.data);

    cv::Mat flipped;
    cv::flip(pixels, flipped, 0);

    std::string filename = "screenshot.png";

    if (cv::imwrite(filename, flipped))
        std::cout << "Screenshot saved\n";
    else
        std::cout << "Screenshot failed\n";
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    World::getCamera()->processMouse(xoffset, yoffset);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    World::getCamera()->processScroll((float)yoffset);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_F) {
            toggleFullscreen(window);
        }
        if (key == GLFW_KEY_V) {
            toggleVSync();
        }
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, true);
        }
        if (key == GLFW_KEY_P) {
            takeScreenshot(window);
        }
    }
}

bool Renderer::init()
{
    if (!glfwInit()) {
        std::cerr << "GLFW init failed\n";
        return false;
    }

    // macOS OpenGL limit
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    window = glfwCreateWindow(800, 600, "ICP Project", nullptr, nullptr);
    if (!window) {
        std::cerr << "Window creation failed\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // VSync

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK){
        std::cerr << "GLEW init failed\n";
        return false;
    }

    GUI::init(window);

    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    std::cout << "Renderer initialized, window created\n";
    return true;
}

void Renderer::beginFrame()
{
    glfwPollEvents();

    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GUI::beginFrame();
}

void Renderer::endFrame()
{
    GUI::render();
    GUI::endFrame();

    glfwSwapBuffers(window);
}

void Renderer::render()
{
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader* shader = World::getShader();
    Camera* camera = World::getCamera();

    shader->use();

    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = camera->getProjectionMatrix();

    for (auto obj : World::getObjects())
    {
        glm::mat4 model = obj->getModelMatrix();
        glm::mat4 mvp = projection * view * model;

        glUniformMatrix4fv(
            glGetUniformLocation(shader->getID(), "MVP"),
            1,
            GL_FALSE,
            glm::value_ptr(mvp)
        );

        obj->draw();
    }
}

bool Renderer::shouldClose()
{
    return glfwWindowShouldClose(window);
}

GLFWwindow* Renderer::getWindow()
{
    return window;
}

void Renderer::shutdown()
{
    GUI::shutdown();

    glfwDestroyWindow(window);
    glfwTerminate();
}