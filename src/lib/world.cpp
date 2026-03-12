#include "world.hpp"

std::map<std::pair<int,int>, std::vector<Object*>> World::chunkObjects;
float World::elapsedTime = 0.0f;
ChunkManager World::chunkManager;

static Material* terrainMaterial;
static Material* cubeMaterial;
static Material* coinMaterial;
static Material* treeMaterial;

static Model* cubeModel;
static Model* coinModel;
static Model* treeModel;

std::set<std::pair<int,int>> World::loadedChunks;

void World::init()
{
    Shader* shader = new Shader(
        "resources/shaders/vertex.glsl",
        "resources/shaders/fragment.glsl"
    );

    Texture* grass = new Texture("resources/textures/grass.png");
    Texture* brick = new Texture("resources/textures/brick.png");
    Texture* tree = new Texture("resources/textures/tree.png");
    Texture* coin = new Texture("resources/textures/coin_alb.png");

    terrainMaterial = new Material(shader, grass);
    cubeMaterial    = new Material(shader, brick);
    coinMaterial    = new Material(shader, coin);
    treeMaterial    = new Material(shader, tree);
    
    cubeModel = new Model("resources/obj/cube.obj");
    coinModel = new Model("resources/obj/coin.obj");
    treeModel = new Model("resources/obj/tree.obj");

    chunkManager.start();

    updateChunksAroundCamera();
}

void World::update(float delta)
{
    elapsedTime += delta;

    updateChunksAroundCamera();

    Chunk* chunk = chunkManager.getReadyChunk();

    if (chunk)
    {
        std::pair<int,int> key = {chunk->x, chunk->z};

        Mesh* mesh = new Mesh(
            chunk->vertices.data(),
            chunk->vertices.size() * sizeof(float)
        );

        Object* terrain = new Object(mesh, terrainMaterial);
        chunkObjects[key].push_back(terrain);

        int seed = chunk->x * 73856093 ^ chunk->z * 19349663;
        int type = abs(seed) % 10;

        float size = 10.0f;
        float worldX = chunk->x * size + size * 0.5f;
        float worldZ = chunk->z * size + size * 0.5f;

        if (type == 0)
        {
            Object* cube = new Object(cubeModel, cubeMaterial);

            glm::vec3 pos(worldX, 1.0f, worldZ);
            cube->setBasePosition(pos);

            int animType = abs(seed ^ 0xABCDEF) % 3;
            float offset = (seed % 100) * 0.1f;
            float speed  = 0.5f + (abs(seed) % 50) / 100.0f;

            cube->configureAnimation(animType, offset, speed);

            int soundId = Audio::createSpatialSound("resources/audio/levitation.mp3", pos, true);

            cube->setSoundId(soundId);

            chunkObjects[key].push_back(cube);
        }
        else if (type == 1) {
            Object* rock = new Object(treeModel, treeMaterial);

            glm::vec3 pos(worldX, 0.0f, worldZ);
            rock->setBasePosition(pos);

            chunkObjects[key].push_back(rock);
        }
        else if (type == 3) {
            Object* coin = new Object(coinModel, coinMaterial);

            glm::vec3 pos(worldX, 1.0f, worldZ);
            coin->setBasePosition(pos);

            float offset = (seed % 100) * 0.1f;
            float speed  = 0.5f + (abs(seed) % 50) / 100.0f;

            coin->configureAnimation(1, offset, speed);

            chunkObjects[key].push_back(coin);
        }

        delete chunk;
    }

    for (auto& [chunkKey, objects] : chunkObjects)
    {
        for (auto obj : objects)
        {
            obj->update(elapsedTime);

            if (obj->getSoundId() != -1)
            {
                glm::vec3 camPos = Renderer::getCamera()->getPosition();
                glm::vec3 objPos = obj->getPosition();

                float dist = glm::distance(camPos, objPos);

                Audio::setSoundPosition(obj->getSoundId(), objPos);
            }
        }
    }
}

void World::updateChunksAroundCamera()
{
    glm::vec3 camPos = Renderer::getCamera()->getPosition();

    int chunkX = static_cast<int>(floor(camPos.x / 10.0f));
    int chunkZ = static_cast<int>(floor(camPos.z / 10.0f));

    int radius = 5;

    removeFarChunks(chunkX, chunkZ, radius);

    for (int x = -radius; x <= radius; x++)
    {
        for (int z = -radius; z <= radius; z++)
        {
            std::pair<int,int> key = {chunkX + x, chunkZ + z};

            if (loadedChunks.find(key) == loadedChunks.end())
            {
                chunkManager.requestChunk(key.first, key.second);
                loadedChunks.insert(key);
            }
        }
    }
}

void World::removeFarChunks(int currentChunkX, int currentChunkZ, int radius)
{
    std::vector<std::pair<int,int>> toRemove;

    for (auto& pair : loadedChunks)
    {
        int dx = pair.first - currentChunkX;
        int dz = pair.second - currentChunkZ;

        if (abs(dx) > radius || abs(dz) > radius)
        {
            toRemove.push_back(pair);
        }
    }

    for (auto& key : toRemove)
    {
        loadedChunks.erase(key);

        if (chunkObjects.count(key))
        {
            for (auto obj : chunkObjects[key])
                delete obj;

            chunkObjects.erase(key);
        }

    }
}

const std::vector<Object*>& World::getObjects()
{
    static std::vector<Object*> temp;
    temp.clear();

    for (auto& pair : chunkObjects)
        for (auto obj : pair.second)
            temp.push_back(obj);

    return temp;
}

void World::shutdown(){
    chunkManager.stop();
}