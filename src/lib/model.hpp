#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

#include "mesh.hpp"

class Model {
    public:
        Model(const std::string& path);
        void draw() const;

    private:
        Mesh* mesh;
};