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

class AudioManager : public Module
{
public:
	AudioManager();
	~AudioManager();

	void Init() override;
	void Update(sf::Time dt) override;
	void Destroy() override;

	std::shared_ptr<SoundManager> GetSoundManager();
	std::shared_ptr<SoundBuffer> GetSoundBuffer();

protected:
	std::shared_ptr<SoundManager> m_SoundManager = nullptr;
	std::shared_ptr<SoundBuffer> m_SoundBuffer = nullptr;
};

class SoundBuffer
{
public:
	/**
	* \brief load a buffer for the sound
	*/
	unsigned int LoadSoundBuffer(std::string filename);
	/**
	* \brief return the buffer 
	*/
	std::shared_ptr<sf::SoundBuffer> GetSoundBuffer(unsigned int sound_buffer_id);

private:
	std::map<std::string, unsigned int> bufferIdPath;
	std::map<unsigned int, std::shared_ptr<sf::SoundBuffer>> soundBufferMap;
	unsigned int increment_id = 0;
};

class Sound : public Singleton<Sound>
{
public:
	/**
	* \brief load a sf::sound and return
	*/
	static std::shared_ptr<sf::Sound> LoadSound(json& componentJson);
	/**
	* \brief set the buffer for the sound
	*/
	void SetSoundBuffer(std::shared_ptr<sf::SoundBuffer> newSoundBuffer);
	void Play(sf::Sound& sound);

protected:
	std::string filename;
	sf::Sound sound;
};

class SoundManager
{
public:
	SoundManager(AudioManager& audioManager);
	/**
	* \brief load a sound from a path file
	*/
	void LoadSound(json& componentJson, std::shared_ptr<sf::Sound> newSound);
	~SoundManager();
protected:
	std::list<std::shared_ptr<sf::Sound>> m_Sounds;
	AudioManager& m_AudioManager;
};

class MusicManager : public Singleton<MusicManager>
{
public:
	/**
	* \brief load a music from a path file
	*/
	unsigned int LoadMusic(std::string filename);
	std::shared_ptr<sf::Music> GetMusic(unsigned int musicId);
	/**
	* \brief play the music
	*/
	void PlayMusic(sf::Music& music);
	/**
	* \brief pause the given music
	*/
	void PauseMusic(sf::Music& music);
	/**
	* \brief stop the music, if play it start from the beginning
	*/
	void StopMusic(sf::Music& music);
	/**
	* \brief choose if the music loop or not
	*/
	void SetLoop(sf::Music music, bool loop);
	/**
	* \brief Set the volume of the music from 0 (mute) to 100(normal)
	*/
	void SetVolume(sf::Music& music, int volume);

protected:
	sf::Music music;
	std::map< std::string , unsigned int> musicPathId;
	std::map<unsigned int, std::shared_ptr<sf::Music>> musicMap;
	std::string filename;
	unsigned int increment_id = 0;
};
}
#endif // !SFGE_AUDIO
