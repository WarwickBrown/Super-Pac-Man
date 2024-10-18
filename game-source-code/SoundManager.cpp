/**
 * @file SoundManager.cpp
 * @brief Implements the methods of the SoundManager class for handling sound effects.
 * 
 * This file contains the definitions of the methods declared in SoundManager.h.
 * It provides functionality for loading, playing, stopping, and unloading sound effects,
 * as well as managing the internal sound map.
 */

#include "SoundManager.h"
#include <sstream>
#include <iostream>

SoundManager::SoundManager() {
    InitAudioDevice();  ///< Initialise audio device.
    loadAllSounds();    ///< Preload all sounds.
}

SoundManager::~SoundManager() {
    unloadAllSounds();  ///< Unload all sounds when the manager is destroyed.
    CloseAudioDevice();  ///< Close the audio device.
}

void SoundManager::loadAllSounds() {
    // Load each sound file and store it with a unique identifier.
    sounds["power_pellet"] = LoadSound("../resources/audio-files/power-pickup.wav");
    sounds["super_pellet"] = LoadSound("../resources/audio-files/super-pacman.wav");
    sounds["fruit_collect"] = LoadSound("../resources/audio-files/fruit-pickup.wav");
    sounds["key_collect"] = LoadSound("../resources/audio-files/open-door.wav");
    sounds["star_collect"] = LoadSound("../resources/audio-files/star-pickup.wav");
    sounds["ghost_eaten"] = LoadSound("../resources/audio-files/ghost-eaten.wav");
    sounds["lose_life"] = LoadSound("../resources/audio-files/pacman-wilhelm.wav");
    sounds["win_game"] = LoadSound("../resources/audio-files/win-game.wav");
    sounds["lose_game"] = LoadSound("../resources/audio-files/game-lose.wav");
    sounds["start_screen_music"] = LoadSound("../resources/audio-files/start-screen-music.wav");
    sounds["gameplay_music"] = LoadSound("../resources/audio-files/gameplay-music.wav");
}

void SoundManager::loadSound(const std::string& name, const std::string& filePath) {
    if (sounds.find(name) == sounds.end()) {
        sounds[name] = LoadSound(filePath.c_str());
    }
}

void SoundManager::playSound(const std::string& name) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        PlaySound(it->second);
    } else {
        std::cerr << "Sound not found: " << name << std::endl;
    }
}

void SoundManager::stopSound(const std::string& name) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        StopSound(it->second);
    } else {
        std::cerr << "Sound not found: " << name << std::endl;
    }
}

void SoundManager::unloadAllSounds() {
    for (auto& sound : sounds) {
        UnloadSound(sound.second);
    }
    sounds.clear();
}