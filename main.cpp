#include <iostream>

#include "src/lib/renderer.hpp"

int main()
{
    if (!Renderer::init()) {
        return -1;
    }

    while (!Renderer::shouldClose()) {
        Renderer::beginFrame();

        Renderer::endFrame();
    }

    Renderer::shutdown();
    return 0;
}
