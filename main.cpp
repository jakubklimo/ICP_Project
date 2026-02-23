#include <iostream>

#include "src/lib/renderer.hpp"

int main()
{
    Renderer::init();

    World::init();

    float lastFrame = 0.0f;

    while (!Renderer::shouldClose())
    {
        Renderer::beginFrame();

        float currentFrame = glfwGetTime();
        float delta = currentFrame - lastFrame;
        lastFrame = currentFrame;

        Renderer::getCamera()->processKeyboard(Renderer::getWindow(), delta);
        World::update(delta);

        Renderer::render();

        Renderer::endFrame();
    }

    World::shutdown();
    Renderer::shutdown();
    return 0;
}
