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

#include <graphics/sprite.h>

uint TextureManager::load_texture(std::string filename)
{
    if(nameIdsMap.find(filename) != nameIdsMap.end())
    {
        return nameIdsMap[filename];
    }
    else
    {
        increment_id++;
        sf::Texture texture;
        if (!texture.loadFromFile(filename))
            return 0U;
        nameIdsMap[filename] = increment_id;
        texturesMap[increment_id] = texture;
    }
    return 0U;
}



uint TextureManager::get_last_id()
{
    return increment_id;
}

//TODO: unload texture from text_id
void TextureManager::unload_texture(uint text_id)
{
    
}

sf::Texture* TextureManager::get_texture(uint text_id)
{
    if(texturesMap.find(text_id) != texturesMap.end())
    {
        return &texturesMap[text_id];
    }
    return NULL;
}
