#pragma once

#include <string>
#include <GL/glew.h>
#include <iostream>

class Shader {
    public:
        Shader(const char* vertexSrc, const char* fragmentSrc);
        ~Shader();

        void use() const;
        unsigned int getID() const { return programID; }

    private:
        unsigned int programID;
};