#include "world.h"

#include <iostream>
#include <sstream>

void World::BuildGridMap()
{
    for (int i = 0; i < m_Tilesets.size(); ++i)
    {
        for (uint32_t g = m_Tilesets[i].firstGid; g <= m_Tilesets[i].lastGid; ++g)
            m_GidToTileset[g] = i;
    }
}

void World::BuildLayerVertices(tinyxml2::XMLElement* map)
{
}

std::vector<uint32_t> World::ParseCSV(tinyxml2::XMLElement* layer_data)
{
    std::vector<uint32_t> gids;
    gids.reserve(m_MapWidth * m_MapHeight);
    {
        std::string raw = layer_data->GetText() ? layer_data->GetText() : "";
        std::stringstream ss(raw);
        std::string item;
        while (std::getline(ss, item, ','))
        {
            size_t s = item.find_first_not_of(" \t\r\n");
            size_t e = item.find_last_not_of(" \t\r\n");
            if (s == std::string::npos)
            {
                gids.push_back(0);
            } 
            else 
            {
                gids.push_back((uint32_t)std::strtoull(item.substr(s, e - s + 1).c_str(), nullptr, 10));
            }
        }
    }

    return gids;
}

void World::ParseTilesets(tinyxml2::XMLElement* map, std::vector<sf::Texture*>& textures)
{
    int globalTW = map->IntAttribute("tilewidth");
    int globalTH = map->IntAttribute("tileheight");
    
    size_t texIndex = 0;
    uint32_t maxLast = 0;
    for (auto* ts = map->FirstChildElement("tileset"); ts; ts = ts->NextSiblingElement("tileset"))
    {
        if (texIndex >= textures.size()) break;

        uint32_t first = ts->UnsignedAttribute("firstgid");
        int tileCount  = ts->IntAttribute("tilecount");
        int columns    = ts->IntAttribute("columns");
        int tileWidth  = ts->IntAttribute("tilewidth",  globalTW);
        int tileHeight = ts->IntAttribute("tileheight", globalTH);

        uint32_t last = first + tileCount - 1;
        maxLast = std::max(maxLast, last);

        Tileset info;
        info.firstGid = first;
        info.lastGid  = last;
        info.tex      = textures[texIndex++];
        info.tileW    = tileWidth;
        info.tileH    = tileHeight;
        info.columns  = columns;
        m_Tilesets.push_back(info);
    }

    m_GidToTileset.assign(maxLast + 1, -1);
}

tinyxml2::XMLElement* World::LoadXML(const std::string& tmx_file)
{
    m_Tilesets.clear();
    m_GidToTileset.clear();
    m_Document.Clear();

    if (m_Document.LoadFile(tmx_file.c_str()) != tinyxml2::XML_SUCCESS)
    {
        std::cerr << "Failed to load XML file from path: " << tmx_file << std::endl;
        return nullptr;
    }

    auto* map = m_Document.FirstChildElement("map");
    if (!map)
    {
        std::cerr << "Could not find map element in file: " << tmx_file << std::endl;
        return nullptr;
    }

    return map;
}

bool World::OnLoad(const std::string& tmx_file, std::vector<sf::Texture*>& textures)
{
    tinyxml2::XMLElement* map = LoadXML(tmx_file);

    ParseTilesets(map, textures);
    BuildGridMap();
    
    for (auto* layerNode = map->FirstChildElement("layer"); layerNode; layerNode = layerNode->NextSiblingElement("layer"))
    {
        Layer layer;
        layer.data = GetDataFromLayer(layerNode);
        std::vector<uint32_t> gids = ParseCSV(layer.data);

		std::vector<size_t> counts(m_Tilesets.size(), 0);
		for (const auto gid : gids) if (gid && gid < m_GidToTileset.size()) 
		{
			int idx = m_GidToTileset[gid];
			if (idx >= 0) counts[idx]++;
		}

        layer.vertices.resize(m_Tilesets.size());
        for (int i = 0; i < m_Tilesets.size(); ++i)
        {
            layer.vertices[i].setPrimitiveType(sf::PrimitiveType::Triangles);
			layer.vertices[i].resize(counts[i] * 6);
        }

		std::vector<size_t> writePos(m_Tilesets.size(), 0);

		for (int y = 0; y < m_MapHeight; ++y) 
		{
			for (int x = 0; x < m_MapWidth; ++x) 
			{
				uint32_t gid = gids[y * m_MapWidth + x];
				if (!gid || gid >= m_GidToTileset.size()) continue;
				int tsIndex = m_GidToTileset[gid];
				if (tsIndex < 0) continue;

				Tileset& ts = m_Tilesets[tsIndex];
				uint32_t localId = gid - ts.firstGid;
				int tu = localId % ts.columns;
				int tv = localId / ts.columns;

				auto px = (float)(x * ts.tileW);
				auto py = (float)(y * ts.tileH);
				auto tx = (float)(tu * ts.tileW);
				auto ty = (float)(tv * ts.tileH);

				size_t base = writePos[tsIndex] * 6;
				sf::Vertex* v = &layer.vertices[tsIndex][base];

				v[0] = sf::Vertex{ { px,              py } };           v[0].texCoords = { tx,              ty };
				v[1] = sf::Vertex{ { px + ts.tileW,   py } };           v[1].texCoords = { tx + ts.tileW,   ty };
				v[2] = sf::Vertex{ { px + ts.tileW,   py + ts.tileH } };v[2].texCoords = { tx + ts.tileW,   ty + ts.tileH };
				v[3] = sf::Vertex{ { px,              py } };           v[3].texCoords = { tx,              ty };
				v[4] = sf::Vertex{ { px + ts.tileW,   py + ts.tileH } };v[4].texCoords = { tx + ts.tileW,   ty + ts.tileH };
				v[5] = sf::Vertex{ { px,              py + ts.tileH } };v[5].texCoords = { tx,              ty + ts.tileH };

				writePos[tsIndex]++;
			}
		}

        m_Layers.push_back(layer);
    }

    return true;
}

tinyxml2::XMLElement* World::GetDataFromLayer(tinyxml2::XMLElement* layer_element)
{
    if (!layer_element) return nullptr;
    m_MapWidth  = layer_element->IntAttribute("width");
    m_MapHeight = layer_element->IntAttribute("height");

    auto* data = layer_element->FirstChildElement("data");
    if (!data) return nullptr;
    const char* enc = data->Attribute("encoding");
    if (enc && std::string(enc) != "csv") return nullptr;

    return data;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int l = 0; l < m_Layers.size(); l++)
    {
        for (int t = 0; t < m_Tilesets.size(); t++)
        {
			states.texture = m_Tilesets[t].tex;
			target.draw(m_Layers[l].vertices[t], states);
        }
    }
}



