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


class Transform : public Component
{
public:
	using Component::Component;
	~Transform();
	static std::shared_ptr<Transform> LoadTransform(json& componentJson, GameObject& gameObject);

	void Update(float dt) override;

	const float GetEulerAngle();
	void SetEulerAngle(float eulerAngle);
	const sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f position);
	const sf::Vector2f GetScale();
	void SetScale(sf::Vector2f scale);

private:
	sf::Vector2f m_Position = sf::Vector2f(0.0f,0.0f);
	sf::Vector2f m_Scale = sf::Vector2f(1.0f,1.0f);
	float m_EulerAngle = 0.0f;

};

}

#endif /* INCLUDE_ENGINE_TRANSFORM_H_ */
