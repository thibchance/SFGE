/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef SFGE_AUDIO_H
#define SFGE_AUDIO_H
#include <engine/engine.h>
#include <engine/component.h>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include "utility/json_utility.h"

namespace sfge
{
class SoundBuffer;
class SoundManager;
class Sound;
class MusicManager;

class AudioManager : public Module
{
public:
	using Module::Module;
	/**
	* \brief construct the AudioManager
	* \param engine use for init the module
	* \param enable use for ImGui 
	*/
	AudioManager(Engine& engine, bool enable = true);
	/**
	* \brief Initialize SoundManager class, SoundBuffer class and MusicManager class
	*/
	void Init() override;
	/**
	* \brief Update the audioManager, called only in play mode
	* \ param dt The delta time since last frame
	*/
	void Update(sf::Time dt) override;
	/**
	* \brief delete the AudioManager
	*/
	void Destroy() override;
	/**
	* \brief return a SoundManager class
	*/
	std::shared_ptr<SoundManager> GetSoundManager();
	/**
	* \brief return a SoundBuffer class
	*/
	std::shared_ptr<SoundBuffer> GetSoundBuffer();
	/**
	* \brief return a MusicManager class
	*/
	std::shared_ptr<MusicManager> GetMusicManager();

protected:
	std::shared_ptr<SoundManager> m_SoundManager = nullptr;
	std::shared_ptr<SoundBuffer> m_SoundBuffer = nullptr;
	std::shared_ptr<MusicManager> m_MusicManager = nullptr;
};

class SoundBuffer
{
public:
	/**
	* \brief load a sf::SoundBuffer, put it on soundBufferMap and return the matchin id
	* \param filename The filename of the buffer file
	*/
	unsigned int LoadSoundBuffer(std::string filename);
	/**
	* \brief return the sf::SoundBuffer attached to the given sound_buffer_id on the soundBufferMap
	* \param sound_buffer_id The id key of the soundBuffer
	*/
	std::shared_ptr<sf::SoundBuffer> GetSoundBuffer(unsigned int sound_buffer_id);

private:
	std::map<std::string, unsigned int> bufferIdPath;
	std::map<unsigned int, std::shared_ptr<sf::SoundBuffer>> soundBufferMap;
	unsigned int increment_id = 0;
};
/**
* \brief Sound class child is a Component
*/
class Sound : public Component
{
public:
	using Component::Component;
	/**
	* \brief initialize the Sound class
	*/
	void Init() override;
	/**
	* \brief Update the audioManager, called only in play mode
	* \ param dt The delta time since last frame
	*/
	void Update(float dt) override;
	/**
	* \brief create a sf::Sound, call LoadSound of SoundManager class and return the created sound
	* \param engine The engine using for create a dynamic_pointer_cast of audio_manager 
	* \param componentJson The json using when call LoadSound of SoundManager class
	* \param gameObject The GameObject which the sound is attached
	*/
	static std::shared_ptr<sf::Sound> LoadSound(Engine& engine, json& componentJson, GameObject* gameObject);
};

class SoundManager
{
public:
	SoundManager(AudioManager& audioManager);
	/**
	* \brief load a buffer from a json["path"] and ad it to the newSound
	* \param componentJson The json using for load a sf::SoundBuffer when call LoadSoundBuffer from SoundBuffer class
	* \param newSound The sound where sf::SoundBuffer was set 
	*/
	void LoadSound(json& componentJson, std::shared_ptr<sf::Sound> newSound);
	~SoundManager();
protected:
	/**
	* \brief The list where the sounds of LoadSound fuction of SoundManager was placed
	*/
	std::list<std::shared_ptr<sf::Sound>> m_Sounds;
	AudioManager& m_AudioManager;
};

class MusicManager 
{
public:
	/**
	* \brief open a music from a path file, put it on MusicMap and return the matchin id
	* \param filename The filename of the music file
	*/
	unsigned int LoadMusic(std::string filename);
	/**
	* \brief return the music attached to the given musicId on MusicMap
	* \param musicId the id key of the music
	*/
	std::shared_ptr<sf::Music> GetMusic(unsigned int musicId);

protected:
	std::map< std::string , unsigned int> musicPathId;
	std::map<unsigned int, std::shared_ptr<sf::Music>> musicMap;
	unsigned int increment_id = 0;
};
}
#endif // !SFGE_AUDIO
