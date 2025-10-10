#pragma once

#include "entity.h"

#include <SFML/Graphics.hpp>

class Camera
{
public:
	void SetViewPoint(sf::RenderWindow& window);
	void SetCenterPoint(const sf::Vector2f& center_point, sf::RenderWindow& window);
private:
	sf::View m_View;
};

