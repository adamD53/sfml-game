#include "terrain.hpp"
#include "static_entity.hpp"

#include <memory>
#include <print>
#include <vector>

Terrain::~Terrain()
{
    for (const auto& staticEntity : m_StaticEntities)
        if (staticEntity) delete staticEntity;
}

auto Terrain::BuildGridMap() -> void
{
    for (int i = 0; i < m_Tilesets.size(); ++i)
    {
        for (uint32_t g = m_Tilesets[i].firstGid; g <= m_Tilesets[i].lastGid; ++g)
            m_GidToTileset[g] = i;
    }
}

auto Terrain::BuildLayerVertices(tinyxml2::XMLElement* map) -> void
{
    for (auto* layerNode = map->FirstChildElement("layer"); layerNode; layerNode = layerNode->NextSiblingElement("layer"))
    {

        Layer layer;
        layer.data = GetDataFromLayer(layerNode);
        layer.name = layerNode->FindAttribute("name")->Value();
        std::vector<uint32_t> gids = ParseCSV(layer.data);

		std::vector<size_t> counts(m_Tilesets.size(), 0);
		for (const auto gid : gids) if (gid && gid < m_GidToTileset.size()) 
		{
			const int idx = m_GidToTileset[gid];
			if (idx >= 0) counts[idx]++;
		}

        layer.vertices.resize(m_Tilesets.size());
        for (int i = 0; i < m_Tilesets.size(); ++i)
        {
            layer.vertices[i].setPrimitiveType(sf::PrimitiveType::Triangles);
			layer.vertices[i].resize(counts[i] * 6);
        }

		std::vector<size_t> writePos(m_Tilesets.size(), 0);

        
        // TODO: refactor this to create one tree object, not individual tile. Make tree objects in tiled
        // if (!layer.name.compare("trees"))
        // {
        //     for (uint32_t y = 0; y < m_MapHeight; ++y) 
        //     {
        //         for (uint32_t x = 0; x < m_MapWidth; ++x) 
        //         {
        //             const uint32_t gid = gids[y * m_MapWidth + x];
        //             if (!gid || gid >= m_GidToTileset.size()) continue;
        //             const uint32_t tsIndex = m_GidToTileset[gid];
        //             if (tsIndex < 0) continue;
        
        //             const Tileset& ts      = m_Tilesets[tsIndex];
        //             const uint32_t localId = gid - ts.firstGid;
        //             const uint32_t tu      = localId % ts.columns;
        //             const uint32_t tv      = localId / ts.columns;
        
        //             auto px = (float)(x * ts.tileW);
        //             auto py = (float)(y * ts.tileH);
        //             auto tx = (float)(tu * ts.tileW);
        //             auto ty = (float)(tv * ts.tileH);
        
        //             Entity* staticEntity = new StaticEntity(px, py, tx, ty, ts.tex); 
        //             m_StaticEntities.push_back(staticEntity);
        //         }
        //     }
        //     continue;
        // }

		for (uint32_t y = 0; y < m_MapHeight; ++y) 
		{
			for (uint32_t x = 0; x < m_MapWidth; ++x) 
			{
				const uint32_t gid = gids[y * m_MapWidth + x];
				if (!gid || gid >= m_GidToTileset.size()) continue;
				const uint32_t tsIndex = m_GidToTileset[gid];
				if (tsIndex < 0) continue;

				const Tileset& ts      = m_Tilesets[tsIndex];
				const uint32_t localId = gid - ts.firstGid;
				const uint32_t tu      = localId % ts.columns;
				const uint32_t tv      = localId / ts.columns;

				auto px = (float)(x * ts.tileW);
				auto py = (float)(y * ts.tileH);
				auto tx = (float)(tu * ts.tileW);
				auto ty = (float)(tv * ts.tileH);

				size_t base   = writePos[tsIndex] * 6;
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
}

auto Terrain::ParseCSV(tinyxml2::XMLElement* layer_data) -> std::vector<uint32_t>
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

auto Terrain::ParseTilesets(tinyxml2::XMLElement* map, std::unordered_map<std::string, std::unique_ptr<sf::Texture>>& textures) -> void
{
    const auto globalTW = map->IntAttribute("tilewidth");
    const auto globalTH = map->IntAttribute("tileheight");
    
    uint32_t maxLast = 0;
    for (auto* ts = map->FirstChildElement("tileset"); ts; ts = ts->NextSiblingElement("tileset"))
    {
        const auto first      = ts->UnsignedAttribute("firstgid");
        const auto tileCount  = ts->IntAttribute("tilecount");
        const auto columns    = ts->IntAttribute("columns");
        const auto tileWidth  = ts->IntAttribute("tilewidth",  globalTW);
        const auto tileHeight = ts->IntAttribute("tileheight", globalTH);
        const auto tileName  = ts->Attribute("name");

        if (!tileName)
        {
            std::println("Error reading tileset name.");
            break;
        }

        uint32_t last = first + tileCount - 1;
        maxLast = std::max(maxLast, last);

        Tileset info;
        info.firstGid = first;
        info.lastGid  = last;
        info.tex      = textures[tileName].get();
        info.tileW    = tileWidth;
        info.tileH    = tileHeight;
        info.columns  = columns;
        m_Tilesets.push_back(info);
    }

    m_GidToTileset.assign(maxLast + 1, -1);
}

auto Terrain::LoadXML(const std::string& tmx_file) -> tinyxml2::XMLElement*
{
    m_Tilesets.clear();
    m_GidToTileset.clear();
    m_Document.Clear();

    if (m_Document.LoadFile(tmx_file.c_str()) != tinyxml2::XML_SUCCESS)
    {
        std::println(stderr, "CFailed to load XML file from path: {0}", tmx_file);
        return nullptr;
    }

    auto* map = m_Document.FirstChildElement("map");
    if (!map)
    {
        std::println(stderr, "Could not find map element in file: {0}", tmx_file);
        return nullptr;
    }

    return map;
}

auto Terrain::Load(const std::string& tmx_file, std::unordered_map<std::string, std::unique_ptr<sf::Texture>>& textures) -> void
{
    tinyxml2::XMLElement* map = LoadXML(tmx_file);
    
    m_MapWidth  = map->IntAttribute("width");
    m_MapHeight = map->IntAttribute("height");

    ParseTilesets(map, textures);
    BuildGridMap();
    BuildLayerVertices(map);
}

auto Terrain::GetDataFromLayer(tinyxml2::XMLElement* layer_element) -> tinyxml2::XMLElement*
{
    if (!layer_element) return nullptr;

    auto* data = layer_element->FirstChildElement("data");
    if (!data) return nullptr;
    const char* enc = data->Attribute("encoding");
    if (enc && std::string(enc) != "csv") return nullptr;

    return data;
}

auto Terrain::GetStaticEntities() -> std::vector<Entity*> const
{
    return m_StaticEntities;
}

void Terrain::draw(sf::RenderTarget& target, sf::RenderStates states) const
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



