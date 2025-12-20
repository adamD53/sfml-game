#pragma once

#include <SFML/Graphics.hpp>

#include "tinyxml2.h"
#include "static_entity.hpp"

#include <vector>
#include <unordered_map>

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
    std::string name;
};

class World : public sf::Drawable, sf::Transformable
{
public:
	World() = default;
	~World() = default;

public:
	void Load(const std::string& tmx_file, std::unordered_map<std::string, sf::Texture*>& textures);
    auto GetStaticEntities() -> std::vector<StaticEntity*> const;

private:
	std::vector<Tileset> m_Tilesets;
	std::vector<int> m_GidToTileset;
    std::vector<StaticEntity*> m_StaticEntities;
	tinyxml2::XMLDocument m_Document;
	std::vector<Layer> m_Layers;

	uint32_t m_MapWidth = 0;
	uint32_t m_MapHeight = 0;

private:
	auto LoadXML(const std::string& tmx_file) -> tinyxml2::XMLElement*;
	auto ParseTilesets(tinyxml2::XMLElement* map, std::unordered_map<std::string, sf::Texture*>& textures) -> void;
	auto ParseCSV(tinyxml2::XMLElement* map) -> std::vector<uint32_t>;
	auto GetDataFromLayer(tinyxml2::XMLElement* map) -> tinyxml2::XMLElement*;
	auto BuildGridMap() -> void;
	auto BuildLayerVertices(tinyxml2::XMLElement* map) -> void;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};






