#pragma once

#include <string>
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader {
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        void use() const;
        unsigned int getID() const { return programID; }

    private:
        unsigned int programID;
};