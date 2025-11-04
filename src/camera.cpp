#include "camera.h"

auto Camera::SetViewPoint(sf::RenderWindow& window) -> void
{
	m_View = window.getDefaultView();
	m_View.zoom(0.5f);
	
	window.setView(m_View);
}

auto Camera::SetCenterPoint(const sf::Vector2f& center_point, sf::RenderWindow& window) -> void
{
    sf::Vector2f viewHalfSize = m_View.getSize() / 2.f;

    float minX = LEFT_BOUND + viewHalfSize.x;
    float maxX = RIGHT_BOUND - viewHalfSize.x;
    float minY = TOP_BOUND + viewHalfSize.y;
    float maxY = BOTTOM_BOUND - viewHalfSize.y;

    float clampedX = std::clamp(center_point.x, minX, maxX);
    float clampedY = std::clamp(center_point.y, minY, maxY);
    
    m_View.setCenter({ clampedX, clampedY });
    window.setView(m_View);
}
