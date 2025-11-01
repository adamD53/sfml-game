#pragma once

#include "entity.h"

#include <SFML/Graphics.hpp>

#include <memory>

class Player : public Entity
{
public:
	Player();
	~Player() = default;

	void OnUpdate(float dt) override;
	void OnDraw(sf::RenderWindow& window) override;
	sf::Vector2f GetPos() const override;

private:
	sf::Texture m_Texture;
	std::unique_ptr<sf::Sprite> m_Sprite;
	bool m_FacingRight = false;
};

