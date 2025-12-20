#pragma once

#include <SFML/Graphics.hpp>

class StaticEntity
{
public:
    StaticEntity(float posX, float posY, float texX, float texY, const sf::Texture* texture);
    ~StaticEntity();
    
    auto GetSprite() -> sf::Sprite&;

private:
    float m_PosX, m_PosY, m_TexX, m_TexY;
    sf::Sprite m_Sprite; 
};
