#include "static_entity.hpp"

StaticEntity::StaticEntity(float posX, float posY, float texX, float texY, const sf::Texture* texture)
    :m_PosX(posX), m_PosY(posY), m_TexX(texX), m_TexY(texY), m_Sprite(*texture)
{
    m_Sprite.setTextureRect(sf::IntRect({ (int)m_TexX, (int)m_TexY }, { 16, 16 } ));
    m_Sprite.setPosition({ m_PosX, m_PosY });
}

StaticEntity::~StaticEntity()
{
}


auto StaticEntity::GetSprite() -> sf::Sprite&
{
    return m_Sprite;
}
