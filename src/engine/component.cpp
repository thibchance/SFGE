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

#include <engine/component.h>
namespace sfge
{

Component::Component(GameObject& parentObject) :
	gameObject(parentObject)
{

}

std::shared_ptr<Transform> Transform::LoadTransform(json& componentJson, GameObject& gameObject)
{
	std::shared_ptr<Transform> newTransform = std::make_shared<Transform>(gameObject);
	if (CheckJsonParameter(componentJson, "position", json::value_t::array))
	{
		auto positionJson = componentJson["position"].array();
		if (positionJson.size() == 2)
		{
			sf::Vector2f newPosition;
			if (IsJsonValueNumeric(positionJson[0]))
			{
				newPosition.x = positionJson[0];
			}
			if (IsJsonValueNumeric(positionJson[1]))
			{
				newPosition.y = positionJson[1];
			}
			newTransform->SetPosition(newPosition);
		}
	}
	if (CheckJsonParameter(componentJson, "scale", json::value_t::array))
	{
		auto scaleJson = componentJson["scale"].array();
		if (scaleJson.size() == 2)
		{
			sf::Vector2f newScale;
			if (IsJsonValueNumeric(scaleJson[0]))
			{
				newScale.x = scaleJson[0];
			}
			if (IsJsonValueNumeric(scaleJson[1]))
			{
				newScale.y = scaleJson[1];
			}
			newTransform->SetScale(newScale);
		}
	}
	if (CheckJsonExists(componentJson, "angle"))
	{
		if (IsJsonValueNumeric(componentJson["angle"]))
		{
			newTransform->SetEulerAngle(componentJson["angle"]);
		}
	}
	return newTransform;
}

void Transform::Update(float dt)
{

}

const float Transform::GetEulerAngle()
{
	return m_EulerAngle;
}

void Transform::SetEulerAngle(float eulerAngle)
{
	this->m_EulerAngle = eulerAngle;
}

const sf::Vector2f Transform::GetPosition()
{
	return m_Position;
}

void Transform::SetPosition(sf::Vector2f position)
{
	this->m_Position = position;
}

const sf::Vector2f Transform::GetScale()
{
	return m_Scale;
}

void Transform::SetScale(sf::Vector2f scale)
{
	this->m_Scale = scale;
}
}
