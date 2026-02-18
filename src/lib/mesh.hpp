#pragma once

#include <cstddef>
#include <GL/glew.h>

class Mesh {
    public:
        Mesh(const float* vertices, size_t size);
        ~Mesh();

        void draw() const;

    private:
        unsigned int VAO;
        unsigned int VBO;
        size_t vertexCount;
};