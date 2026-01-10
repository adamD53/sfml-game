#pragma once

#include <SFML/Graphics.hpp>

class PlayerGUI
{
public:
    PlayerGUI(sf::RenderWindow* window);
    ~PlayerGUI() = default;

public:
    auto Render() -> void;
    auto Update(float& playerHP) -> void;

private:
    sf::RectangleShape m_HealthBar;
    sf::RectangleShape m_BackgroundBar;
    sf::RenderWindow* m_Window;

private:
    auto CalculateHealthBarPosition() -> sf::Vector2f const;
};
