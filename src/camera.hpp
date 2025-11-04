#pragma once

#include "entity.hpp"

#include <SFML/Graphics.hpp>
#include "global_config.hpp"

class Camera
{
public:
	auto SetViewPoint(sf::RenderWindow& window) -> void;
	auto SetCenterPoint(const sf::Vector2f& center_point, sf::RenderWindow& window) -> void;
private:
	sf::View m_View;
	sf::FloatRect m_MapBounds;
};

