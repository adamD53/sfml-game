#pragma once

#include "player.hpp"
#include "terrain.hpp"
#include "camera.hpp"
#include "projectile.hpp"

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
	~Game() = default;
	auto Run() -> void;
    auto CheckForBounds(const sf::Vector2f& position) -> bool;
private:
	sf::RenderWindow m_Window;
	Terrain m_Terrain;
    std::vector<std::unique_ptr<Entity>> m_Entities;
    std::vector<std::unique_ptr<Projectile>> m_Projectiles;
	Player m_Player;
	std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_Tilesets;
	Camera m_Camera;
};
