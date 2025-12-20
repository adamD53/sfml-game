#pragma once

#include "player.hpp"
#include "static_entity.hpp"
#include "terrain.hpp"
#include "camera.hpp"

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

struct GameSpecification
{
	const uint32_t width, height;
	const std::string title;
};

class Game
{
public:
	Game(const GameSpecification& spec);
	~Game();
	auto Run() -> void;
private:
	sf::RenderWindow m_Window;
	Terrain m_Terrain;
    std::vector<StaticEntity*> m_StaticEntities;
    std::vector<Entity*> m_Entities;
	std::unique_ptr<Player> m_Player;
	std::unordered_map<std::string, sf::Texture*> m_Tilesets;
	Camera m_Camera;
};
