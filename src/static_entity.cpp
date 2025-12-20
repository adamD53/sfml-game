#include "static_entity.hpp"
#include "SFML/Graphics/VertexBuffer.hpp"

StaticEntity::StaticEntity(float posX, float posY, float texX, float texY, const sf::Texture* texture)
    :m_PosX(posX), m_PosY(posY), m_TexX(texX), m_TexY(texY), m_Sprite(*texture)
{
    m_Sprite.setTextureRect(sf::IntRect({ (int)m_TexX, (int)m_TexY }, { 16, 16 } ));
    m_Sprite.setPosition({ m_PosX, m_PosY });
}

auto StaticEntity::GetSprite() -> sf::Sprite&
{
    return m_Sprite;
}

auto StaticEntity::GetPos() -> sf::Vector2f const
{
    return m_Sprite.getPosition();
}

void StaticEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Sprite, states);
}

