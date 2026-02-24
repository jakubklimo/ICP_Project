#include "model.hpp"

Model::Model(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Failed to open OBJ file");

    std::vector<glm::vec3> tempVertices;
    std::vector<glm::vec2> tempTexCoords;
    std::vector<glm::vec3> tempNormals;

    std::vector<float> vertices;

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
        else if (prefix == "vn")
        {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            tempNormals.push_back(normal);
        }
        else if (prefix == "vt")
        {
            glm::vec2 tex;
            ss >> tex.x >> tex.y;
            tempTexCoords.push_back(tex);
        }
        else if (prefix == "f")
        {
            std::vector<std::string> faceVertices;
            std::string vStr;

            while (ss >> vStr)
                faceVertices.push_back(vStr);

            auto parseVertex = [&](std::string v)
            {
                std::replace(v.begin(), v.end(), '/', ' ');
                std::stringstream vs(v);

                unsigned int vi = 0, ti = 0, ni = 0;
                vs >> vi >> ti >> ni;

                return std::tuple<unsigned int, unsigned int, unsigned int>(
                    vi - 1,
                    ti > 0 ? ti - 1 : 0,
                    ni > 0 ? ni - 1 : 0
                );
            };

            auto process = [&](std::string vStr)
            {
                auto [vi, ti, ni] = parseVertex(vStr);

                glm::vec3 pos = tempVertices[vi];
                glm::vec2 uv  = tempTexCoords.empty() ? glm::vec2(0,0) : tempTexCoords[ti];
                glm::vec3 norm = tempNormals.empty() ? glm::vec3(0,1,0) : tempNormals[ni];

                vertices.push_back(pos.x);
                vertices.push_back(pos.y);
                vertices.push_back(pos.z);

                vertices.push_back(uv.x);
                vertices.push_back(uv.y);

                vertices.push_back(norm.x);
                vertices.push_back(norm.y);
                vertices.push_back(norm.z);
            };

            // 🔥 triangulace fan metodou
            for (size_t i = 1; i + 1 < faceVertices.size(); i++)
            {
                process(faceVertices[0]);
                process(faceVertices[i]);
                process(faceVertices[i + 1]);
            }
        }
    }

    mesh = new Mesh(vertices.data(), vertices.size() * sizeof(float));
}

void Model::draw() const
{
    mesh->draw();
}