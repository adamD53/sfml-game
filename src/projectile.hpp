#pragma once

#include "entity.hpp"

class Projectile : public Entity
{
public:
    Projectile(const sf::Vector2f& playerPosition, const sf::Vector2f& direction);
    ~Projectile() = default;

    auto SetPosition(const sf::Vector2f& posistion) -> void;
    auto SetPlayerPosition(const sf::Vector2f& posistion) -> void;
    auto OnUpdate(float dt) -> void override;
    auto GetPos() -> sf::Vector2f const override;
    auto GetBounds() -> sf::FloatRect const override;

private:
    sf::Vector2f m_PlayerPosition;
    sf::Vector2f m_Direction;
    float m_Speed;
    sf::CircleShape m_Sprite;
    sf::Texture m_Texture;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
