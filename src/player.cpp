#include "player.hpp"
#include "global_config.hpp"

Player::Player()
{
	m_Textures.emplace(std::make_pair("walk_down", sf::Texture("resources/player/Walk_Down-Sheet.png")));
	m_Textures.emplace(std::make_pair("walk_up", sf::Texture("resources/player/Walk_Up-Sheet.png")));
	m_Textures.emplace(std::make_pair("walk_side", sf::Texture("resources/player/Walk_Side-Sheet.png")));
	m_Textures.emplace(std::make_pair("idle_down", sf::Texture("resources/player/Idle_Down-Sheet.png")));

	m_Sprite = std::make_unique<sf::Sprite>(m_Textures["idle_down"]);
	m_Sprite->setTextureRect(sf::IntRect({ 16, 16 }, { 32, 32 }));
	auto [width, height] = m_Sprite->getTextureRect().size;
	m_Sprite->setOrigin({ 16 / 2.f, height / 2.f });
	m_Sprite->setPosition({ 500, 300 });

	m_Animation = std::make_unique<Animation>(0.2f);
}

auto Player::GetPos() -> sf::Vector2f const
{
	return sf::Vector2f(m_Sprite->getPosition());
}

auto Player::OnUpdate(float dt) -> void
{
	sf::Vector2f direction(0.0f, 0.0f);
	uint32_t currentAnimationFrameIndex = 0;
	int animationRow = 0;
	
	m_CurrentState = PlayerState::IdleDown; 

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && (Player::GetPos().x > config::leftBound))
	{
		direction.x += -1.0f;
		m_CurrentState = PlayerState::WalkLeft;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && (Player::GetPos().x < config::rightBound))
	{
		direction.x += 1.0f;
		m_CurrentState = PlayerState::WalkRight;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && (Player::GetPos().y > config::topBound))
	{
		direction.y += -1.0f;
		m_CurrentState = PlayerState::WalkUp;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && (Player::GetPos().y < config::bottomBound))
	{
		direction.y += 1.0f;
		m_CurrentState = PlayerState::WalkDown;
	}

	const uint32_t framesCount = (m_CurrentState == PlayerState::IdleDown) ? 4 : 6;
	currentAnimationFrameIndex = m_Animation->Update(framesCount);

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
	m_Sprite->setTextureRect(sf::IntRect({ frameX, animationRow }, { config::playerTextureWidth, config::playerTextureHeight }));
	
	m_Sprite->move((direction.length() <= 1 ? direction : direction.normalized()) * m_Speed * dt);
	m_Sprite->setScale({ (m_FacingRight ? 1.0f : -1.0f), 1.0f});
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*m_Sprite, states);
}






