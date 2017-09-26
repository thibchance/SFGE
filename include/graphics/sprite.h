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

#ifndef SFGE_SPRITE_H
#define SFGE_SPRITE_H

//STL
#include <map>
#include <string>

//Engine
#include <engine/engine.h>
#include <engine/component.h>
//Dependencies
#include <SFML/Graphics.hpp>

class Sprite : public Component
{
protected:
	std::string filename;
	sf::Sprite* sprite;
};

class SpriteManager : public Module<SpriteManager>
{
protected:
	std::list<sf::Sprite> sprites;
};

//Storing all the texture file
class TextureManager : public Module<TextureManager>
{
public:
	unsigned int load_texture(std::string);
	unsigned int get_last_id();
    void unload_texture(unsigned int);
    
    sf::Texture* get_texture(unsigned int);
private:
    std::map<std::string, unsigned int> nameIdsMap;
    std::map<unsigned int, sf::Texture> texturesMap;
	std::map<unsigned int, unsigned int> refCountMap;
	unsigned int increment_id = 0;
};


#endif // !SFGE_SPRITE
