#include "material.hpp"

Material::Material(Shader* shader, Texture* texture)
    : shader(shader), texture(texture)
{}

void Material::bind() const
{
    shader->use();
    texture->bind(0);
}

Shader* Material::getShader() const
{
    return shader;
}