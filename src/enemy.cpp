#include "enemy.hpp"

Enemy::Enemy(Entity* target)
    : m_Target(target)
{
    std::uniform_real_distribution<float> dist(0.0f, 1000.0f);
    std::uniform_int_distribution<int> dist_speed(50, 100);
    float randomX = dist(s_RandomDevice);
    float randomY = dist(s_RandomDevice);
    m_Speed = dist_speed(s_RandomDevice);

    m_Sprite.setSize({50, 50});
    m_Sprite.setPosition({randomX, randomY});
    m_Sprite.setFillColor(sf::Color::Red);
}

auto Enemy::GetBounds() -> sf::FloatRect const
{
    return m_Sprite.getGlobalBounds();
}

auto Enemy::GetPos() -> sf::Vector2f const
{
    return m_Sprite.getPosition();
}

auto Enemy::OnUpdate(float dt) -> void
{
    m_Direction = m_Target->GetPos() - (Enemy::GetPos() + sf::Vector2f(10.f, 10.f));
    m_Sprite.move(m_Direction.normalized() * dt * m_Speed);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Sprite, states);
}
