#pragma once

#include "camera.hpp"
#include "player.hpp"
#include "player_gui.hpp"
#include "projectile.hpp"
#include "terrain.hpp"

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <unordered_map>
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

private:
    sf::RenderWindow m_Window;
    std::vector<std::unique_ptr<Entity>> m_Entities;
    std::vector<Projectile> m_Projectiles;
    Terrain m_Terrain;
    Player m_Player;
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_Tilesets;
    std::unique_ptr<Camera> m_Camera;
    std::unique_ptr<PlayerGUI> m_PlayerGUI;

private:
    auto CheckForBounds(const sf::Vector2f& position) -> bool const;
};
