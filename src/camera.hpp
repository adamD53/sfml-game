#pragma once

#include <SFML/Graphics.hpp>

class Camera
{
public:
	auto SetViewPoint(sf::RenderWindow& window) -> void;
	auto SetCenterPoint(const sf::Vector2f& centerPoint, sf::RenderWindow& window) -> void;
private:
	sf::View m_View;
};

