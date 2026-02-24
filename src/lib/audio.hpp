#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>

#include "miniaudio.h"

class Audio {
    public:
        static bool init();
        static void shutdown();

        static void updateListener(const glm::vec3& pos, const glm::vec3& forward);

        static void playMusic(const std::string& path, bool loop = true);

        static int createSpatialSound(const std::string& path, const glm::vec3& position, bool loop = true);

        static void setSoundPosition(int id, const glm::vec3& position);

    private:
        static ma_engine engine;
        static std::vector<ma_sound*> sounds;
};