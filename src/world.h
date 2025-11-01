#pragma once

#include <SFML/Graphics.hpp>

#include "tinyxml2.h"

#include <vector>
#include <memory>

struct Tileset 
{
    uint32_t firstGid;
    uint32_t lastGid;
    const sf::Texture* tex;
    int tileW;
    int tileH;
    int columns;
};

struct Layer 
{
	std::vector<sf::VertexArray> vertices;
	tinyxml2::XMLElement* data;
};

class World : public sf::Drawable, sf::Transformable
{
public:
	World() = default;
	~World() = default;

public:
	bool OnLoad(const std::string& tmx_file, std::vector<sf::Texture*>& textures);

private:
	std::vector<Tileset> m_Tilesets;
	std::vector<int> m_GidToTileset;
	tinyxml2::XMLDocument m_Document;
	std::vector<Layer> m_Layers;

	int m_MapWidth = 0;
	int m_MapHeight = 0;

private:
	tinyxml2::XMLElement* LoadXML(const std::string& tmx_file);
	void ParseTilesets(tinyxml2::XMLElement* map, std::vector<sf::Texture*>& textures);
	std::vector<uint32_t> ParseCSV(tinyxml2::XMLElement* map);
	tinyxml2::XMLElement* GetDataFromLayer(tinyxml2::XMLElement* map);
	void BuildGridMap();
	void BuildLayerVertices(tinyxml2::XMLElement* map);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

