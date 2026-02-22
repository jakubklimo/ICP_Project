#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "model.hpp"

class Model;

class Object {
    public:
        Object(Model* model);

        void setPosition(const glm::vec3& pos);
        void setRotation(const glm::vec3& rot);

        glm::mat4 getModelMatrix() const;
        void draw() const;

    private:
        Model* model;

        glm::vec3 position;
        glm::vec3 rotation;
};