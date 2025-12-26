#include "projectile.hpp"
#include "SFML/System/Vector2.hpp"
#include "global_config.hpp"

Projectile::Projectile(const sf::Vector2f& playerPosition)
    : m_PlayerPosition(playerPosition), m_Speed(config::projectileSpeed)
{
    m_Sprite.setRadius(2.0f);
    m_Sprite.setFillColor(sf::Color::Black);
    m_Sprite.setPosition(playerPosition);
}

auto Projectile::OnUpdate(float dt) -> void
{
	m_Sprite.move(direction.normalized() * m_Speed * dt);
}

auto Projectile::GetPos() -> sf::Vector2f const
{
    return m_Sprite.getPosition();
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Sprite, states);
}

auto Projectile::SetPosition(const sf::Vector2f& posistion) -> void
{
    m_Sprite.setPosition(posistion);
}

auto Projectile::SetPlayerPosition(const sf::Vector2f& posistion) -> void
{
    m_PlayerPosition = posistion;
}










