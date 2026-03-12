#define MINIAUDIO_IMPLEMENTATION

#include "audio.hpp"

ma_engine Audio::engine;
std::vector<ma_sound*> Audio::sounds;

bool Audio::init()
{
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS)
    {
        std::cerr << "Failed to init audio engine\n";
        return false;
    }

    ma_engine_listener_set_world_up(&engine, 0, 0.0f, 1.0f, 0.0f);

    std::cout << "Audio initialized\n";
    return true;
}

void Audio::shutdown()
{
    for (auto s : sounds)
    {
        ma_sound_uninit(s);
        delete s;
    }

    ma_engine_uninit(&engine);
}

void Audio::updateListener(const glm::vec3& pos, const glm::vec3& forward)
{
    ma_engine_listener_set_position(&engine, 0, pos.x, pos.y, pos.z);

    ma_engine_listener_set_direction(&engine, 0, forward.x, forward.y, forward.z);
}

void Audio::playMusic(const std::string& path, bool loop)
{
    ma_sound* music = new ma_sound;

    if (ma_sound_init_from_file(&engine, path.c_str(), 0, NULL, NULL, music) != MA_SUCCESS)
    {
        std::cerr << "Failed to load music\n";
        delete music;
        return;
    }

    ma_sound_set_looping(music, loop);
    ma_sound_start(music);

    sounds.push_back(music);
}

int Audio::createSpatialSound(const std::string& path, const glm::vec3& position, bool loop)
{
    ma_sound* sound = new ma_sound;

    if (ma_sound_init_from_file(&engine, path.c_str(), 0, NULL, NULL, sound) != MA_SUCCESS)
    {
        std::cerr << "Failed to load spatial sound\n";
        delete sound;
        return -1;
    }

    ma_sound_set_spatialization_enabled(sound, MA_TRUE);
    ma_sound_set_position(sound, position.x, position.y, position.z);

    ma_sound_set_min_distance(sound, 1.0f);
    ma_sound_set_max_distance(sound, 80.0f);
    ma_sound_set_rolloff(sound, 2.0f);

    ma_sound_set_attenuation_model(sound, ma_attenuation_model_inverse);

    ma_sound_set_looping(sound, loop);
    ma_sound_start(sound);

    sounds.push_back(sound);
    return (int)sounds.size() - 1;
}

void Audio::setSoundPosition(int id, const glm::vec3& position)
{
    if (id < 0 || id >= sounds.size())
        return;

    ma_sound_set_position(sounds[id], position.x, position.y, position.z);
}