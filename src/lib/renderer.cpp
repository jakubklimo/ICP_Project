#include "renderer.hpp"
#include <iostream>

GLFWwindow* Renderer::window = nullptr;
Camera* Renderer::camera = nullptr;

static bool firstMouse = true;
static float lastX = 400, lastY = 300;

bool Renderer::fullscreen = false;
bool Renderer::vsync = true;
bool Renderer::msaa = true;

int Renderer::savedPosX = 0;
int Renderer::savedPosY = 0;
int Renderer::savedWidth = 800;
int Renderer::savedHeight = 600;

void Renderer::toggleFullscreen()
{
    fullscreen = !fullscreen;

    GLFWwindow* window = getWindow();

    if (fullscreen)
    {
        glfwGetWindowPos(window, &savedPosX, &savedPosY);
        glfwGetWindowSize(window, &savedWidth, &savedHeight);

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else
    {
        glfwSetWindowMonitor(window, nullptr, savedPosX, savedPosY, savedWidth, savedHeight, 0);
    }

    firstMouse = true;

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    if (camera)
        camera->setAspect((float)width / (float)height);
}

void Renderer::toggleVSync()
{
    vsync = !vsync;
    glfwSwapInterval(vsync ? 1 : 0);

    std::cout << "VSync: " 
              << (vsync ? "ON" : "OFF") 
              << std::endl;
}

void Renderer::toggleMSAA()
{
    msaa = !msaa;

    if (msaa)
        glEnable(GL_MULTISAMPLE);
    else
        glDisable(GL_MULTISAMPLE);

    std::cout << "MSAA: "
              << (msaa ? "ON" : "OFF")
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

    Renderer::getCamera()->processMouse(xoffset, yoffset);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Renderer::getCamera()->processScroll((float)yoffset);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_F) {
            Renderer::toggleFullscreen();
        }
        if (key == GLFW_KEY_V) {
            Renderer::toggleVSync();
        }
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, true);
        }
        if (key == GLFW_KEY_P) {
            takeScreenshot(window);
        }
        if (key == GLFW_KEY_M) {
            Renderer::toggleMSAA();
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
    glfwWindowHint(GLFW_SAMPLES, 4);

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
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    float aspect = (float)width / (float)height;
    camera = new Camera(45.0f, aspect, 0.1f, 100.0f);

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

    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = camera->getProjectionMatrix();

    for (auto obj : World::getObjects())
    {
        Shader* shader = obj->getMaterial()->getShader();

        shader->use();

        glm::mat4 model = obj->getModelMatrix();
        glm::mat4 mvp = projection * view * model;

        glUniformMatrix4fv(glGetUniformLocation(shader->getID(), "MVP"), 1, GL_FALSE, glm::value_ptr(mvp));

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
    delete camera;
    camera = nullptr;

    GUI::shutdown();

    glfwDestroyWindow(window);
    glfwTerminate();
}

Camera* Renderer::getCamera()
{
    return camera;
}

bool Renderer::isFullscreen() { return fullscreen; }
bool Renderer::isVSync() { return vsync; }
bool Renderer::isMSAA() { return msaa; }