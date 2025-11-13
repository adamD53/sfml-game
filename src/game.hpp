#pragma once

#include "entity.hpp"
#include "player.hpp"
#include "world.hpp"
#include "camera.hpp"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

struct GameSpecification
{
	int width, height;
	std::string title;
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
	std::vector<sf::Texture*> m_Tilesets; // TODO: Change texture container to hashmap
	std::vector<Entity*> m_Entities;
	Camera m_Camera;
};
