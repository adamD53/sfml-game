#include "player_gui.hpp"

#include <print>

PlayerGUI::PlayerGUI(sf::RenderWindow* window)
    : m_Window(window)
{
    m_HealthBar.setSize({90.f, 30.f});
    m_HealthBar.setPosition({10, 10});
    m_HealthBar.setFillColor(sf::Color::Red);
    
    m_BackgroundBar.setSize({150.f, 30.f});
    m_BackgroundBar.setPosition({10, 10});
    m_BackgroundBar.setFillColor(sf::Color::Black);
}

auto PlayerGUI::Update(float& playerHP) -> void
{
    std::println("Health points: {0}", playerHP);
}

auto PlayerGUI::Render() -> void
{
    m_Window->draw(m_BackgroundBar);
    m_Window->draw(m_HealthBar);
}
