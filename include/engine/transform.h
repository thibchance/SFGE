/*
 * transform.h
 *
 *  Created on: Feb 6, 2018
 *      Author: efarhan
 */

#ifndef SFGE_TRANSFORM_H_
#define SFGE_TRANSFORM_H_

#include <engine/component.h>

namespace sfge
{

/**
* \brief Mandatory Component of a GameObject, showing its geometric characteristics
*/
class Transform : public Component
{
public:
	using Component::Component;
	/**
	* \brief Factory method to create the Transform Component
	*/
	static Transform* LoadTransform(json& componentJson, GameObject* gameObject);
	/**
	* \brief Initialize the Transform
	*/
	void Init() override;
	/**
	* \brief Called each frame
	*/
	void Update(float dt) override;
	/**
	* \brief Getter of the euler angle
	*/
	const float GetEulerAngle();
	/**
	* \brief Setter of the euleur angle
	*/
	void SetEulerAngle(float eulerAngle);
	/**
	* \brief Getter of the position
	*/
	const sf::Vector2f GetPosition();
	/**
	* \brief Setter of the position
	*/
	void SetPosition(sf::Vector2f position);
	/**
	* \brief Getter of the scale
	*/
	const sf::Vector2f GetScale();
	/**
	* \brief Setter of the scale
	*/
	void SetScale(sf::Vector2f scale);

private:
	sf::Vector2f m_Position = sf::Vector2f(0.0f,0.0f);
	sf::Vector2f m_Scale = sf::Vector2f(1.0f,1.0f);
	float m_EulerAngle = 0.0f;

};

}

#endif /* INCLUDE_ENGINE_TRANSFORM_H_ */
