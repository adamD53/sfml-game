#include "camera.h"

void Camera::SetViewPoint(sf::RenderWindow& window)
{
	m_View = window.getDefaultView();
	m_View.zoom(1.0f);
	
	window.setView(m_View);
}

void Camera::SetCenterPoint(const sf::Vector2f& center_point, sf::RenderWindow& window)
{
	m_View.setCenter(center_point);
	window.setView(m_View);
}
