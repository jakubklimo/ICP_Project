#include "chunk_manager.hpp"

ChunkManager::ChunkManager()
    : running(false)
{}

ChunkManager::~ChunkManager()
{
    stop();
}

void ChunkManager::start()
{
    running = true;
    worker = std::thread(&ChunkManager::workerLoop, this);
}

void ChunkManager::stop()
{
    running = false;
    cv.notify_all();

    if (worker.joinable())
        worker.join();
}

void ChunkManager::requestChunk(int x, int z)
{
    {
        std::lock_guard<std::mutex> lock(mutex);
        requestQueue.push({x,z});
    }
    cv.notify_one();
}

Chunk* ChunkManager::getReadyChunk()
{
    std::lock_guard<std::mutex> lock(mutex);

    if (readyQueue.empty())
        return nullptr;

    Chunk* c = readyQueue.front();
    readyQueue.pop();
    return c;
}

void ChunkManager::workerLoop()
{
    while (running)
    {
        std::pair<int,int> task;

        {
            std::unique_lock<std::mutex> lock(mutex);

            cv.wait(lock, [&]() {
                return !requestQueue.empty() || !running;
            });

            if (!running)
                break;

            task = requestQueue.front();
            requestQueue.pop();
        }

        Chunk* chunk = new Chunk();
        chunk->x = task.first;
        chunk->z = task.second;

        float size = 10.0f;

        float worldX = chunk->x * size;
        float worldZ = chunk->z * size;

        chunk->vertices = {
            worldX, 0, worldZ, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            worldX+size, 0, worldZ+size, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            worldX+size, 0, worldZ, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            worldX, 0, worldZ, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            worldX, 0, worldZ+size, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            worldX+size, 0, worldZ+size, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f
        };

        {
            std::lock_guard<std::mutex> lock(mutex);
            readyQueue.push(chunk);
        }
    }
}