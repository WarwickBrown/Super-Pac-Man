/**
 * @file SoundManager.h
 * @brief Declares the SoundManager class, which manages the loading, playing, and unloading of sound effects.
 * 
 * The SoundManager class encapsulates audio management in the game, providing methods to load, play,
 * stop, and unload sounds. It helps maintain a clean separation of sound logic from other game components.
 */

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <raylib-cpp.hpp>
#include <string>
#include <unordered_map>

/**
 * @class SoundManager
 * @brief Manages sound effects within the game, including loading, playing, and unloading sounds.
 * 
 * The SoundManager class is responsible for handling audio operations, ensuring that sound files
 * are loaded once and played efficiently. It uses an internal map to keep track of all loaded sounds.
 * This design reduces code duplication and centralises sound handling in one place.
 */
class SoundManager {
public:    
    /**
     * @brief Constructs a new SoundManager object and initialises the audio device.
     * 
     * The constructor initialises the audio device required for playing sounds. This
     * must be called before any sound operations are performed.
     */
    SoundManager();

    /**
     * @brief Destroys the SoundManager object and closes the audio device.
     * 
     * The destructor unloads all loaded sounds and closes the audio device to free resources.
     */
    ~SoundManager();

    /**
     * @brief Loads a sound from a given file path and stores it with a unique name.
     * 
     * @param name A unique identifier for the sound (e.g., "power_pickup").
     * @param filePath The relative or absolute path to the sound file to load.
     * 
     * If the sound is already loaded under the given name, it will not be reloaded.
     */
    void loadSound(const std::string& name, const std::string& filePath);

    /**
     * @brief Plays a sound by its unique name.
     * 
     * @param name The name of the sound to play (e.g., "power_pickup").
     * 
     * If the sound is not found in the sound map, this function does nothing.
     */
    void playSound(const std::string& name);

    /**
     * @brief Stops a sound that is currently playing by its unique name.
     * 
     * @param name The name of the sound to stop (e.g., "power_pickup").
     * 
     * If the sound is not found in the sound map, this function does nothing.
     */
    void stopSound(const std::string& name);

    /**
     * @brief Unloads all sounds currently loaded in the manager.
     * 
     * This function ensures that all sound resources are released before the
     * SoundManager is destroyed.
     */
    void unloadAllSounds();

private:
    /**
     * @brief Loads all necessary sound files into the sound map.
     * 
     * This function preloads all sounds used in the game, associating each with a unique name.
     */
    void loadAllSounds();  ///< Load all sound files during initialisation.
    std::unordered_map<std::string, Sound> sounds;  ///< Map storing all loaded sounds, identified by a unique name.
};

#endif