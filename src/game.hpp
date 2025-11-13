#pragma once

#include "entity.hpp"
#include "player.hpp"
#include "world.hpp"
#include "camera.hpp"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <unordered_map>

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
	World m_World;
	Player* m_Player;
	std::unordered_map<std::string, sf::Texture*> m_Tilesets;
	std::vector<Entity*> m_Entities;
	Camera m_Camera;
};
