#pragma once

#include "entity.hpp"

#include <random>

class Enemy : public Entity
{
public:
    Enemy(Entity* target);
    ~Enemy() = default;

    auto GetPos() -> sf::Vector2f const override;
    auto OnUpdate(float dt) -> void override;
    auto GetBounds() -> sf::FloatRect const override;

private:
    sf::RectangleShape m_Sprite;
    float m_Speed = 100.f;
    Entity* m_Target;
    sf::Vector2f m_Direction;
    float timer = 0.0f;

    inline static std::mt19937 s_RandomDevice;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
