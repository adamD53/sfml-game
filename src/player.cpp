#include "player.h"

#include "global_config.h"

#include <iostream>

Player::Player()
	:m_Texture("resources/player/Walk_Down-Sheet.png"),
	m_Sprite(std::make_unique<sf::Sprite>(m_Texture))
{
	m_Sprite->setTextureRect(sf::IntRect({ 16, 16}, { 32, 32 }));
	auto [width, height] = m_Sprite->getTextureRect().size;
	m_Sprite->setOrigin(sf::Vector2f(width / 2.f, height / 2.f));
	m_Sprite->setPosition({ 500, 300 });
}

auto Player::OnDraw(sf::RenderWindow& window) -> void
{
	window.draw(*m_Sprite);
}

auto Player::GetPos() -> sf::Vector2f const
{
	return sf::Vector2f(m_Sprite->getPosition());
}

auto Player::OnUpdate(float dt) -> void
{
	sf::Vector2f direction(0.0f, 0.0f);
	float speed = 150.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && (Player::GetPos().x > config::left_bound))
	{
		direction.x += -1.0f;
		m_FacingRight = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && (Player::GetPos().x < config::right_bound))
	{
		direction.x += 1.0f;
		m_FacingRight = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && (Player::GetPos().y > config::top_bound))
		direction.y += -1.0f;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && (Player::GetPos().y < config::bottom_bound))
	{
		direction.y += 1.0f;
	}

	m_Sprite->move(direction * speed * dt);
	//m_Sprite->setScale({ (m_FacingRight ? 1.0f : -1.0f), 1.0f});
}








