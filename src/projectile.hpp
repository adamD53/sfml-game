#pragma once

#include "SFML/Graphics/CircleShape.hpp"
#include "entity.hpp"

#include <SFML/System/Vector2.hpp>

class Projectile : public Entity
{
public:
    Projectile(const sf::Vector2f& playerPosition);
    ~Projectile() = default;
	
    auto SetPosition(const sf::Vector2f& posistion) -> void;
    auto SetPlayerPosition(const sf::Vector2f& posistion) -> void;
    auto OnUpdate(float dt) -> void override;
    auto GetPos() -> sf::Vector2f const override;
   
public:
    sf::Vector2f direction;

private:
    sf::Vector2f m_PlayerPosition;
    float m_Speed;
    sf::CircleShape m_Sprite;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
