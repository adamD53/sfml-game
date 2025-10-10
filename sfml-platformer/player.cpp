#include "player.h"

#include <iostream>

Player::Player()
	:m_Texture("res/player/player.png"),
	m_Sprite(std::make_unique<sf::Sprite>(m_Texture))
{
	auto [width, height] = m_Texture.getSize();
	m_Sprite->setOrigin(sf::Vector2f(width / 2.f, height / 2.f));
	m_Sprite->setPosition({ 500, 300 });
}

void Player::OnDraw(sf::RenderWindow& window)
{
	window.draw(*m_Sprite);
}

sf::Vector2f Player::GetPos() const
{
	return sf::Vector2f(m_Sprite->getPosition());
}

void Player::OnUpdate(float dt)
{
	sf::Vector2f direction(0.0f, 0.0f);
	float speed = 200.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		direction.x += -1.0f;
		m_FacingRight = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		direction.x += 1.0f;
		m_FacingRight = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		direction.y += -1.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		direction.y += 1.0f;

	m_Sprite->move(direction * speed * dt);
	m_Sprite->setScale({ (m_FacingRight ? 1.0f : -1.0f), 1.0f});
}
