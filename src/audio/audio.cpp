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

namespace sfge
{
void AudioManager::Init()
{

};
void AudioManager::Update(sf::Time dt)
{

};
void AudioManager::Destroy()
{

};
unsigned int SoundBuffer::LoadSoundBuffer(std::string filename)
{
	if (nameIdMap.find(filename) != nameIdMap.end())
	{
		auto sound_buffer_id = nameIdMap[filename];
		auto checkSoundBuffer = soundBufferMap.find(sound_buffer_id);

		if (checkSoundBuffer != soundBufferMap.end())
		{
			return nameIdMap[filename];
		}
		else
		{
			std::shared_ptr<sf::SoundBuffer> soundBuffer = std::make_shared<sf::SoundBuffer>();
			if (!soundBuffer->loadFromFile(filename))
			{
				return 0U;
			}
			nameIdMap[filename] = increment_id;
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
			nameIdMap[filename] = increment_id;
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
}
