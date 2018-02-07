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

#include <audio/audio.h>
#include <iostream>
#include <utility/file_utility.h>

#include <engine/log.h>

namespace sfge
{
	AudioManager::AudioManager()
	{

	}
	AudioManager::~AudioManager()
	{

	}
	void AudioManager::Init()
{
	m_SoundManager = std::make_shared<SoundManager>();
	m_SoundBuffer = std::make_shared<SoundBuffer>();
};
void AudioManager::Update(sf::Time dt)
{

};
void AudioManager::Destroy()
{

}
std::shared_ptr<SoundManager> AudioManager::GetSoundManager()
{
	return m_SoundManager;
}
std::shared_ptr<SoundBuffer> AudioManager::GetSoundBuffer()
{
	return m_SoundBuffer;
}
;
unsigned int SoundBuffer::LoadSoundBuffer(std::string filename)
{
	if (bufferIdPath.find(filename) != bufferIdPath.end())
	{
		auto sound_buffer_id = bufferIdPath[filename];
		auto checkSoundBuffer = soundBufferMap.find(sound_buffer_id);

		if (checkSoundBuffer != soundBufferMap.end())
		{
			return bufferIdPath[filename];
		}
		else
		{
			std::shared_ptr<sf::SoundBuffer> soundBuffer = std::make_shared<sf::SoundBuffer>();
			if (!soundBuffer->loadFromFile(filename))
			{
				return 0U;
			}
			bufferIdPath[filename] = increment_id;
			soundBufferMap[increment_id] = soundBuffer;
			return increment_id;
		}
	}
	else
	{
		if (FileExists(filename))
		{
			increment_id++;
			auto soundBuffer = std::make_shared<sf::SoundBuffer>();

			if (!soundBuffer->loadFromFile(filename))
			{
				return 0U;
			}
			bufferIdPath[filename] = increment_id;
			soundBufferMap[increment_id] = soundBuffer;
			return increment_id;
		}
	}
	return 0U;
}
std::shared_ptr<sf::SoundBuffer> SoundBuffer::GetSoundBuffer(unsigned int sound_buffer_id)
{
	if (soundBufferMap.find(sound_buffer_id) != soundBufferMap.end())
	{
		return soundBufferMap[sound_buffer_id];
	}
	return nullptr;
	
}
std::shared_ptr<sf::Sound> Sound::LoadSound(json & componentJson)
{
	auto audioManager = std::dynamic_pointer_cast<AudioManager>(
		Engine::GetInstance()->GetModule(sfge::EngineModule::AUDIO_MANAGER));
	auto soundManager = audioManager->GetSoundManager();
	if (soundManager != nullptr)
	{
		auto newSound = std::make_shared<sf::Sound>();
		soundManager->LoadSound(componentJson, newSound);
		return newSound;
	}
	return nullptr;
}
void Sound::SetSoundBuffer(std::shared_ptr<sf::SoundBuffer> newSoundBuffer)
{
	sound.setBuffer(*newSoundBuffer);
}
void Sound::Play(sf::Sound& sound)
{
	sound.play();
}
SoundManager::SoundManager(AudioManager & audioManager): m_AudioManager(audioManager)
{

}
void SoundManager::LoadSound(json & componentJson, std::shared_ptr<sf::Sound> newSound)
{
	if (newSound == nullptr)
		return;
	if (CheckJsonParameter(componentJson, "path", json::value_t::string))
	{
		std::string path = componentJson["path"].get<std::string>();
		std::shared_ptr<sf::SoundBuffer> buffer = nullptr;
		if (FileExists(path))
		{
			unsigned int text_id = m_AudioManager.GetSoundBuffer()->LoadSoundBuffer(path);
			if (text_id != 0)
			{
				buffer = m_AudioManager.GetSoundBuffer()->GetSoundBuffer(text_id);
				newSound->setBuffer(*buffer);
			}
		}
		else
		{
			std::ostringstream oss;
			oss << "SoundBuffer file " << path << " does not exist";
			Log::GetInstance()->Error(oss.str());
		}
	}
	else
	{
		Log::GetInstance()->Error("[Error] No Path for Sound");
	}
	m_Sounds.push_back(newSound);
}

SoundManager::~SoundManager()
{
}

unsigned int MusicManager::LoadMusic(std::string filename)
{
	if (musicPathId.find(filename) != musicPathId.end())
	{
		auto musicId = musicPathId[filename];
		auto checkMusic = musicMap.find(musicId);

		if (checkMusic != musicMap.end())
		{
			return musicPathId[filename];
		}
		else
		{
			std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
			if (!music->openFromFile(filename))
			{
				return 0U;
			}
			musicPathId[filename] = increment_id;
			musicMap[increment_id] = music;
			return increment_id;
		}
	}
	else
	{
		if (FileExists(filename))
		{
			increment_id++;
			auto music = std::make_shared<sf::Music>();

			if (!music->openFromFile(filename))
			{
				return 0U;
			}
			musicPathId[filename] = increment_id;
			musicMap[increment_id] = music;
			return increment_id;
		}
	}
	return 0U;
}

std::shared_ptr<sf::Music> MusicManager::GetMusic(unsigned int musicId)
{
	if (musicMap.find(musicId) != musicMap.end())
	{
		return musicMap[musicId];
	}
	return nullptr;
}

}


