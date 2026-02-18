#include "renderer.hpp"
#include <iostream>

GLFWwindow* Renderer::window = nullptr;
static Camera* camera = nullptr;
static Shader* shader = nullptr;
static Mesh* triangleMesh = nullptr;
static Object* triangle = nullptr;
static World* world = nullptr;

static int mvpLocation = -1;

static const char* vertexShaderSrc = R"(
#version 410 core
layout (location = 0) in vec3 aPos;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(aPos, 1.0);
}
)";

static const char* fragmentShaderSrc = R"(
#version 410 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0, 0.3, 0.2, 1.0);
}
)";

static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);

    if (camera) {
        float aspect = (float)width / (float)height;
        camera->setAspect(aspect);
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

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    float aspect = (float)width / (float)height;
    camera = new Camera(45.0f, aspect, 0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST);

    // Create shader
    shader = new Shader(vertexShaderSrc, fragmentShaderSrc);

    shader->use();
    mvpLocation = glGetUniformLocation(shader->getID(), "MVP");

    float vertices[] = {
        0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    triangleMesh = new Mesh(vertices, sizeof(vertices));
    
    world = new World();

    triangle = new Object(triangleMesh);
    triangle->setPosition(glm::vec3(-0.5f, 0.0f, 0.0f));

    Object* triangle2 = new Object(triangleMesh);
    triangle2->setPosition(glm::vec3(0.5f, 0.0f, 0.0f));

    world->addObject(triangle);
    world->addObject(triangle2);

    std::cout << "Renderer initialized, window created\n";
    return true;
}

void Renderer::beginFrame()
{
    glfwPollEvents();

    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float time = glfwGetTime();

    shader->use();

    glm::mat4 view = camera->getViewMatrix();
    glm::mat4 projection = camera->getProjectionMatrix();

    for (auto obj : world->getObjects())
    {
        // jednoduchá animace
        obj->setRotation(glm::vec3(0.0f, time, 0.0f));

        glm::mat4 model = obj->getModelMatrix();
        glm::mat4 mvp = projection * view * model;

        glUniformMatrix4fv(
            mvpLocation,
            1,
            GL_FALSE,
            glm::value_ptr(mvp)
        );

        obj->draw();
    }
}

void Renderer::endFrame()
{
    glfwSwapBuffers(window);
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
    delete triangle;
    delete triangleMesh;
    triangle = nullptr;
    triangleMesh = nullptr;
    delete camera;
    camera = nullptr;

    glfwDestroyWindow(window);
    glfwTerminate();
}