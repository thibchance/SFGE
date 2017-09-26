/*
 MIT License
 
 Copyright (c) 2017 Elias Farhan
 
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
#include <filesystem>

#include "engine/game_object.h"
#include "engine/scene.h"
#include <engine/log.h>

namespace fs = std::experimental::filesystem;

void SceneManager::init()
{
	fs::path scene_data_dir = "data/scenes/";
	if (fs::is_directory(scene_data_dir))
	{
		for (auto& f : fs::directory_iterator(scene_data_dir))
		{
			if (fs::is_regular_file(f))
			{
				auto p = f.path();
				if (p.extension() ==  fs::path(".scene"))
				{
					Log::getInstance()->msg("There is a scene");
				}
			}
		}
	}
	
}

void SceneManager::update(sf::Time)
{
}
