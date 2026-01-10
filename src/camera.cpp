#include "camera.hpp"
#include "global_config.hpp"

Camera::Camera(sf::RenderWindow& window)
{
    m_View = window.getDefaultView();
    m_View.zoom(config::cameraZoomLevel);
}

auto Camera::GetViewPoint() -> sf::View const
{
    return m_View;
}

auto Camera::GetUIViewPoint() -> sf::View const
{
    return m_UIView;
}

auto Camera::SetCenterPoint(const sf::Vector2f& centerPoint) -> void
{
    sf::Vector2f viewHalfSize = m_View.getSize() / 2.f;

    const float minX = config::leftBound + viewHalfSize.x;
    const float maxX = config::rightBound - viewHalfSize.x;
    const float minY = config::topBound + viewHalfSize.y;
    const float maxY = config::bottomBound - viewHalfSize.y;

    const float clampedX = std::clamp(centerPoint.x, minX, maxX);
    const float clampedY = std::clamp(centerPoint.y, minY, maxY);

    m_View.setCenter({clampedX, clampedY});
}

auto Camera::SetUIViewPoint() -> void
{
    float aspect = m_View.getSize().x / m_View.getSize().y;
}
