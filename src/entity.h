#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
public:
	virtual ~Entity() = default;

	virtual void OnDraw(sf::RenderWindow& window) {}
	virtual void OnEvent() {}
	virtual void OnUpdate(float dt) {}
	virtual sf::Vector2f GetPos() const = 0;
};

