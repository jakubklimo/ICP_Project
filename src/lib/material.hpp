#pragma once
#include "shader.hpp"
#include "texture.hpp"

class Material
{
public:
    Material(Shader* shader, Texture* texture);

    void bind() const;
    Shader* getShader() const;

private:
    Shader* shader;
    Texture* texture;
};