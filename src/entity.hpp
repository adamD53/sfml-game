#pragma once

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable
{
public:
	virtual ~Entity() = default;

	virtual auto OnEvent() -> void {}
	virtual auto OnUpdate(float dt) -> void {}
	virtual auto GetPos() -> sf::Vector2f const = 0;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};

