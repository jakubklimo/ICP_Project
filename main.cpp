#include <iostream>

#include "src/lib/renderer.hpp"

int main()
{
    Renderer::init();

    World::init();

    float lastFrame = 0.0f;

    while (!Renderer::shouldClose())
    {
        float currentFrame = glfwGetTime();
        float delta = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        World::update(delta);
        Renderer::render();

        Renderer::endFrame();
    }

    Renderer::shutdown();
    return 0;
}
