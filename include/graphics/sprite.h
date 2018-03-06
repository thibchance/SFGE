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

#ifndef SFGE_SPRITE_H
#define SFGE_SPRITE_H

//STL
#include <map>
#include <string>
//Engine
#include <engine/component.h>
#include <engine/engine.h>
//Dependencies
#include <SFML/Graphics.hpp>

namespace sfge
{
class GraphicsManager;
/**
* \brief Sprite component used in the GameObject
*/
class Sprite : public Component, Offsetable
{
public:
	using Component::Component;
	/**
	* \brief Initialise the Sprite Component
	*/
	void Init() override;
	/**
	* \brief Update the Component
	* \param dt Delta time since last frame
	*/
	void Update(float dt) override;
	/**
	* \brief Draw the SFML sprite on the RenderWindow
	*/
	void Draw(sf::RenderWindow& window);

	/**
	* \brief Factory method to create a Sprite Component
	*/
	static Sprite* LoadSprite(Engine& engine, json& componentJson, GameObject* gameObject);

	/**
	* \brief Setter the Sprite Texture
	*/
	void SetTexture(sf::Texture* newTexture);
	/**
	* \brief Setter the Sprite Texture Id
	*/
	void SetTextureId(unsigned int textureId);
	/**
	* \brief Setter the Sprite layer
	*/
	void SetLayer(int layer);
	/**
	* \brief Sprite layer Comparator, used to sort the sprites when drawing
	*/
	static bool SpriteLayerComp(Sprite* s1, Sprite* s2);
protected:
	sf::Vector2f offset = sf::Vector2f();
	std::string filename;
	unsigned int m_TextureId;
	int layer;
	sf::Sprite sprite;
};

/**
* \brief Sprite manager caching all the sprites and rendering them at the end of the frame
*/
class SpriteManager 
{
public:
	SpriteManager(GraphicsManager& graphicsManager);
	/**
	* \brief Called each frame to sort the sprites 
	*/
	void Update(sf::Time dt);
	/**
	* \brief Draw all the sprites on the RenderWindow
	*/
	void Draw(sf::RenderWindow& window);
	/**
	* \brief Create a Sprite and load it in its maps
	*/
	void LoadSprite(json& componentJson, Sprite* sprite);
	/**
	* \brief Called before the new Scene is loaded
	*/
	void Reset();
	/**
	* \brief Called 
	*/
	void Collect();
protected:
	std::list<Sprite*> m_Sprites;
	GraphicsManager& m_GraphicsManager;
};




}
#endif // !SFGE_SPRITE
