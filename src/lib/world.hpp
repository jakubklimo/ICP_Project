#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "object.hpp"
#include "mesh.hpp"
#include "material.hpp"
#include "texture.hpp"
#include "chunk_manager.hpp"
#include "renderer.hpp"

class Object;

class World {
    public:
        static void init();
        static void update(float delta);

        static const std::vector<Object*>& getObjects();

        static void updateChunksAroundCamera();
        static void removeFarChunks(int currentChunkX, int currentChunkZ, int radius);

        static void shutdown();

    private:
        static ChunkManager chunkManager;
        static Material* defaultMaterial;
        static std::set<std::pair<int,int>> loadedChunks;

        static std::map<std::pair<int,int>, std::vector<Object*>> chunkObjects;
        static float elapsedTime;
};