#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
public:
    Camera(sf::RenderWindow& window);

    auto GetViewPoint() -> sf::View const;
    auto GetUIViewPoint() -> sf::View const;
    
    auto SetUIViewPoint() -> void;
    auto SetCenterPoint(const sf::Vector2f& centerPoint) -> void;

private:
    sf::View m_View, m_UIView;
};
