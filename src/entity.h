#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
public:
	virtual ~Entity() = default;

	virtual auto OnDraw(sf::RenderWindow& window) -> void {}
	virtual auto OnEvent() -> void {}
	virtual auto OnUpdate(float dt) -> void {}
	virtual auto GetPos() -> sf::Vector2f const = 0;
};

