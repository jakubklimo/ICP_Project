#include "model.hpp"

Model::Model(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Failed to open OBJ file");

    std::vector<glm::vec3> tempVertices;
    std::vector<unsigned int> indices;

    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v")
        {
            glm::vec3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            tempVertices.push_back(vertex);
        }
        else if (prefix == "f")
        {
            unsigned int a, b, c;
            ss >> a >> b >> c;

            indices.push_back(a - 1);
            indices.push_back(b - 1);
            indices.push_back(c - 1);
        }
    }

    std::vector<float> vertices;

    for (unsigned int index : indices)
    {
        glm::vec3 v = tempVertices[index];
        vertices.push_back(v.x);
        vertices.push_back(v.y);
        vertices.push_back(v.z);
    }

    mesh = new Mesh(vertices.data(), vertices.size() * sizeof(float));
}

void Model::draw() const
{
    mesh->draw();
}