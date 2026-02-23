#pragma once

#include <queue>
#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <cmath>

#include "chunk.hpp"

class ChunkManager {
    public:
        ChunkManager();
        ~ChunkManager();

        void start();
        void stop();

        void requestChunk(int x, int z);
        Chunk* getReadyChunk();

    private:
        void workerLoop();

        std::queue<std::pair<int,int>> requestQueue;
        std::queue<Chunk*> readyQueue;

        std::mutex mutex;
        std::condition_variable cv;

        std::thread worker;
        std::atomic<bool> running;
};