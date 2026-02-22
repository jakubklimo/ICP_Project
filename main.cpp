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

        World::update(delta);
        World::getCamera()->processKeyboard(Renderer::getWindow(), delta);

        Renderer::render();

        Renderer::endFrame();
    }

    Renderer::shutdown();
    return 0;
}
