#include "player.hpp"
#include "global_config.hpp"

Player::Player()
{
	m_Textures.emplace(std::make_pair("walk_down", sf::Texture("resources/player/Walk_Down-Sheet.png")));
	m_Textures.emplace(std::make_pair("walk_up", sf::Texture("resources/player/Walk_Up-Sheet.png")));
	m_Textures.emplace(std::make_pair("walk_side", sf::Texture("resources/player/Walk_Side-Sheet.png")));
	m_Textures.emplace(std::make_pair("idle_down", sf::Texture("resources/player/Idle_Down-Sheet.png")));

	m_Sprite = std::make_unique<sf::Sprite>(m_Textures["idle"]);
	m_Sprite->setTextureRect(sf::IntRect({ 0, 16}, { 32, 32 }));
	auto [width, height] = m_Sprite->getTextureRect().size;
	m_Sprite->setOrigin(sf::Vector2f(16 / 2.f, height / 2.f));
	m_Sprite->setPosition({ 500, 300 });
	
	m_Animation = std::make_unique<Animation>(0.2f);
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
	const float speed = 150.0f;
	uint32_t currentAnimationFrameIndex = 0;
	int animationRow = 0;
	
	m_CurrentState = PlayerState::IdleDown; 

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && (Player::GetPos().x > config::left_bound))
	{
		direction.x += -1.0f;
		m_CurrentState = PlayerState::WalkLeft;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && (Player::GetPos().x < config::right_bound))
	{
		direction.x += 1.0f;
		m_CurrentState = PlayerState::WalkRight;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && (Player::GetPos().y > config::top_bound))
	{
		direction.y += -1.0f;
		m_CurrentState = PlayerState::WalkUp;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && (Player::GetPos().y < config::bottom_bound))
	{
		direction.y += 1.0f;
		m_CurrentState = PlayerState::WalkDown;
	}

	const uint32_t lastFrame = (m_CurrentState == PlayerState::IdleDown) ? 4 : 6;
	currentAnimationFrameIndex = m_Animation->Update(lastFrame);

	switch (m_CurrentState)
	{
		case PlayerState::IdleDown:
			m_Sprite->setTexture(m_Textures["idle_down"]);
			animationRow = 16;
			break;
		case PlayerState::WalkUp:
			m_Sprite->setTexture(m_Textures["walk_up"]);
			animationRow = 16;
			break;
		case PlayerState::WalkDown:
			m_Sprite->setTexture(m_Textures["walk_down"]);
			animationRow = 16;
			break;
		case PlayerState::WalkRight:
			m_FacingRight = true;
			m_Sprite->setTexture(m_Textures["walk_side"]);
			animationRow = 16;
			break;
		case PlayerState::WalkLeft:
			m_FacingRight = false;
			m_Sprite->setTexture(m_Textures["walk_side"]);
			animationRow = 16;
			break;
	}
	
	int frameX = currentAnimationFrameIndex * m_TexStride;
	m_Sprite->setTextureRect(sf::IntRect({ frameX, animationRow }, { 32, 32 }));
	
	m_Sprite->move((direction.length() <= 1 ? direction : direction.normalized()) * speed * dt);
	m_Sprite->setScale({ (m_FacingRight ? 1.0f : -1.0f), 1.0f});
}








