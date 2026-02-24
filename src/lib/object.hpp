#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "model.hpp"
#include "material.hpp"

class Model;

class Object {
    public:
        Object(Model* model, Material* material);
        Object(Mesh* mesh, Material* material);

        void update(float time);

        void setAnimated(bool value);
        void setBasePosition(const glm::vec3& pos);
        void setPosition(const glm::vec3& pos);
        void setRotation(const glm::vec3& rot);
        void configureAnimation(int type, float offset, float speed);
        void setSoundId(int id);
        int getSoundId() const;

        glm::mat4 getModelMatrix() const;
        void draw() const;

        Material* getMaterial() const;
        glm::vec3 getPosition() const;

    private:
        Model* model;
        Material* material;
        Mesh* mesh;

        glm::vec3 position;
        glm::vec3 rotation;
        bool animated = false;
        float animationOffset = 0.0f;
        glm::vec3 basePosition;
        int animationType = 0;
        float animationSpeed = 1.0f;
        int soundId = -1;
};