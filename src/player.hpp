#pragma once

#include "entity.hpp"

#include <SFML/Graphics.hpp>

#include <memory>

class Player : public Entity
{
public:
	Player();
	~Player() = default;

	auto OnUpdate(float dt) -> void override;
	auto OnDraw(sf::RenderWindow& window) -> void override;
	auto GetPos() -> sf::Vector2f const override;

private:
	sf::Texture m_Texture;
	std::unique_ptr<sf::Sprite> m_Sprite;
	bool m_FacingRight = false;
	
	int m_texWidth = 16;
};

