#include "camera.hpp"
#include "global_config.hpp"

auto Camera::SetViewPoint(sf::RenderWindow& window) -> void
{
	m_View = window.getDefaultView();
	m_View.zoom(0.5f);
	
	window.setView(m_View);
}

auto Camera::SetCenterPoint(const sf::Vector2f& centerPoint, sf::RenderWindow& window) -> void
{
    sf::Vector2f viewHalfSize = m_View.getSize() / 2.f;

    const float minX = config::leftBound + viewHalfSize.x;
    const float maxX = config::rightBound - viewHalfSize.x;
    const float minY = config::topBound + viewHalfSize.y;
    const float maxY = config::bottomBound - viewHalfSize.y;

    const float clampedX = std::clamp(centerPoint.x, minX, maxX);
    const float clampedY = std::clamp(centerPoint.y, minY, maxY);
    
    m_View.setCenter({ clampedX, clampedY });
    window.setView(m_View);
}
