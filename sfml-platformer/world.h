#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

struct Tileset {
    uint32_t firstGid;
    uint32_t lastGid;
    const sf::Texture* tex;
    int tileW;
    int tileH;
    int columns;
    sf::VertexArray vertices; // Triangles
};

class World : public sf::Drawable, sf::Transformable
{
public:
	World() = default;
	~World() = default;

	bool OnLoad(const std::string& tmx_file, std::vector<sf::Texture*>& textures);
private:
	std::vector<Tileset> m_Tilesets;
	std::vector<int> m_GidToTileset;
	int m_MapWidth = 0;
	int m_MapHeight = 0;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

