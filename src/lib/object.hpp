#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "mesh.hpp"

class Mesh;

class Object {
    public:
        Object(Mesh* mesh);

        void setPosition(const glm::vec3& pos);
        void setRotation(const glm::vec3& rot);
        void setScale(const glm::vec3& scale);

        glm::mat4 getModelMatrix() const;
        void draw() const;

    private:
        Mesh* mesh;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
};