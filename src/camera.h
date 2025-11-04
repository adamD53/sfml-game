#pragma once

#define LEFT_BOUND 0
#define TOP_BOUND 0
#define RIGHT_BOUND 1280
#define BOTTOM_BOUND 1000

#include "entity.h"

#include <SFML/Graphics.hpp>

class Camera
{
public:
	auto SetViewPoint(sf::RenderWindow& window) -> void;
	auto SetCenterPoint(const sf::Vector2f& center_point, sf::RenderWindow& window) -> void;
private:
	sf::View m_View;
	sf::FloatRect m_MapBounds;
};

