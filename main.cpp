#include <iostream>

#include "src/lib/renderer.hpp"
#include "src/lib/audio.hpp"

int main()
{
    Renderer::init();

    World::init();

    Audio::init();
    Audio::playMusic("resources/audio/background.mp3");

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
