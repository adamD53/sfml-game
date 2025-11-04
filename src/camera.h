#pragma once

#include "entity.h"

#include <SFML/Graphics.hpp>
#include "global_config.h"

class Camera
{
public:
	auto SetViewPoint(sf::RenderWindow& window) -> void;
	auto SetCenterPoint(const sf::Vector2f& center_point, sf::RenderWindow& window) -> void;
private:
	sf::View m_View;
	sf::FloatRect m_MapBounds;
};

