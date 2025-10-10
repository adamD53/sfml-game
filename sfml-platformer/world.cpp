#include "world.h"

#include "tinyxml2/tinyxml2.h"

#include <iostream>
#include <sstream>

bool World::OnLoad(const std::string& tmx_file, std::vector<sf::Texture*>& textures)
{
    using namespace tinyxml2;
    
    m_Tilesets.clear();
    m_GidToTileset.clear();

    XMLDocument doc;
    if (doc.LoadFile(tmx_file.c_str()) != XML_SUCCESS) return false;

    auto* map = doc.FirstChildElement("map");
    if (!map) return false;

    int globalTW = map->IntAttribute("tilewidth");
    int globalTH = map->IntAttribute("tileheight");

    size_t texIndex = 0;
    uint32_t maxLast = 0;
    for (auto* ts = map->FirstChildElement("tileset"); ts; ts = ts->NextSiblingElement("tileset"))
    {
        if (texIndex >= textures.size()) break;

        uint32_t first = ts->UnsignedAttribute("firstgid");
        int tileCount = ts->IntAttribute("tilecount");
        int columns = ts->IntAttribute("columns");
        int tw = ts->IntAttribute("tilewidth",  globalTW);
        int th = ts->IntAttribute("tileheight", globalTH);

        uint32_t last = first + tileCount - 1;
        maxLast = std::max(maxLast, last);

        Tileset info;
        info.firstGid = first;
        info.lastGid  = last;
        info.tex      = textures[texIndex++];
        info.tileW    = tw;
        info.tileH    = th;
        info.columns  = columns;
        info.vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
        m_Tilesets.push_back(info);
    }

    m_GidToTileset.assign(maxLast + 1, -1);
    for (int i = 0; i < (int)m_Tilesets.size(); ++i)
    {
        for (uint32_t g = m_Tilesets[i].firstGid; g <= m_Tilesets[i].lastGid; ++g)
            m_GidToTileset[g] = i;
    }

    auto* layer = map->FirstChildElement("layer");
    if (!layer) return false;
    m_MapWidth  = layer->IntAttribute("width");
    m_MapHeight = layer->IntAttribute("height");

    auto* data = layer->FirstChildElement("data");
    if (!data) return false;
    const char* enc = data->Attribute("encoding");
    if (enc && std::string(enc) != "csv") return false;

    std::vector<uint32_t> gids;
    gids.reserve(m_MapWidth * m_MapHeight);
    {
        std::string raw = data->GetText() ? data->GetText() : "";
        std::stringstream ss(raw);
        std::string item;
        while (std::getline(ss, item, ',')) {
            size_t s = item.find_first_not_of(" \t\r\n");
            size_t e = item.find_last_not_of(" \t\r\n");
            if (s == std::string::npos) {
                gids.push_back(0);
            } else {
                gids.push_back((uint32_t)std::strtoull(item.substr(s, e - s + 1).c_str(), nullptr, 10));
            }
        }
    }

    std::vector<size_t> counts(m_Tilesets.size(), 0);
    for (auto g : gids) if (g && g < m_GidToTileset.size()) 
    {
        int idx = m_GidToTileset[g];
        if (idx >= 0) counts[idx]++;
    }
    for (int i = 0; i < (int)m_Tilesets.size(); ++i)
        m_Tilesets[i].vertices.resize(counts[i] * 6);

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
            sf::Vertex* v = &ts.vertices[base];

            v[0] = sf::Vertex{ { px,              py } };           v[0].texCoords = { tx,              ty };
			v[1] = sf::Vertex{ { px + ts.tileW,   py } };           v[1].texCoords = { tx + ts.tileW,   ty };
			v[2] = sf::Vertex{ { px + ts.tileW,   py + ts.tileH } };v[2].texCoords = { tx + ts.tileW,   ty + ts.tileH };
			v[3] = sf::Vertex{ { px,              py } };           v[3].texCoords = { tx,              ty };
			v[4] = sf::Vertex{ { px + ts.tileW,   py + ts.tileH } };v[4].texCoords = { tx + ts.tileW,   ty + ts.tileH };
			v[5] = sf::Vertex{ { px,              py + ts.tileH } };v[5].texCoords = { tx,              ty + ts.tileH };

            writePos[tsIndex]++;
        }
    }

    return true;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& ts : m_Tilesets)
    {
        states.texture = ts.tex;
		target.draw(ts.vertices, states);
    }
}



