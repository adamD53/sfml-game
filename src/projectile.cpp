#include "projectile.hpp"
#include "global_config.hpp"

Projectile::Projectile(const sf::Vector2f& playerPosition, const sf::Vector2f& direction)
    : m_PlayerPosition(playerPosition)
    , m_Direction(direction)
    , m_Speed(config::projectileSpeed)
{
    m_Sprite.setRadius(3.f);
    m_Sprite.setFillColor(sf::Color::Black);
    m_Sprite.setPosition(playerPosition);
}

auto Projectile::GetBounds() -> sf::FloatRect const
{
    return sf::FloatRect();
}

auto Projectile::OnUpdate(float dt) -> void
{
    m_Sprite.move((m_Direction.length() > 0.01f ? m_Direction.normalized() : m_Direction) * m_Speed * dt);
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
