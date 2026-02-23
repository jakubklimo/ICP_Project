#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "model.hpp"
#include "material.hpp"

class Model;

class Object {
    public:
        Object(Model* model, Material* material);

        void setPosition(const glm::vec3& pos);
        void setRotation(const glm::vec3& rot);

        glm::mat4 getModelMatrix() const;
        void draw() const;

        Material* getMaterial() const;

    private:
        Model* model;
        Material* material;

        glm::vec3 position;
        glm::vec3 rotation;
};