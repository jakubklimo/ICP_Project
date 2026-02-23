#include "model.hpp"

Model::Model(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Failed to open OBJ file");

    std::vector<glm::vec3> tempVertices;
    std::vector<unsigned int> indices;
    std::vector<glm::vec2> tempTexCoords;
    std::vector<unsigned int> texIndices;

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
        else if (prefix == "vt")
        {
            glm::vec2 tex;
            ss >> tex.x >> tex.y;
            tempTexCoords.push_back(tex);
        }
        else if (prefix == "f")
        {
            std::string v1, v2, v3;
            ss >> v1 >> v2 >> v3;

            auto parseVertex = [&](std::string v)
            {
                std::replace(v.begin(), v.end(), '/', ' ');
                std::stringstream vs(v);

                unsigned int vi, ti;
                vs >> vi >> ti;

                return std::pair<unsigned int, unsigned int>(vi - 1, ti - 1);
            };

            auto p1 = parseVertex(v1);
            auto p2 = parseVertex(v2);
            auto p3 = parseVertex(v3);

            indices.push_back(p1.first);
            indices.push_back(p2.first);
            indices.push_back(p3.first);

            texIndices.push_back(p1.second);
            texIndices.push_back(p2.second);
            texIndices.push_back(p3.second);
        }
    }

    std::vector<float> vertices;

    for (size_t i = 0; i < indices.size(); i++)
    {
        glm::vec3 v = tempVertices[indices[i]];
        glm::vec2 t = tempTexCoords[texIndices[i]];

        vertices.push_back(v.x);
        vertices.push_back(v.y);
        vertices.push_back(v.z);

        vertices.push_back(t.x);
        vertices.push_back(t.y);
    }

    mesh = new Mesh(vertices.data(), vertices.size() * sizeof(float));
}

void Model::draw() const
{
    mesh->draw();
}