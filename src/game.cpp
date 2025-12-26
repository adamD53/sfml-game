#include "game.hpp"
#include "SFML/System/Sleep.hpp"
#include "SFML/System/Time.hpp"
#include "global_config.hpp"
#include "player.hpp"

#include <SFML/Window/Mouse.hpp>

#include <memory>
#include <print>
#include <vector>

Game::Game(const GameSpecification& spec)
{
	m_Window.create(sf::VideoMode(sf::Vector2u(spec.width, spec.height)), spec.title);
	m_Camera.SetViewPoint(m_Window);

	m_Tilesets.emplace(std::pair("Water", std::make_unique<sf::Texture>("resources/world/Water_Tiles.png")));
	m_Tilesets.emplace(std::pair("Floors_Tiles", std::make_unique<sf::Texture>("resources/world/Floors_Tiles.png")));
	m_Tilesets.emplace(std::pair("Trees",  std::make_unique<sf::Texture>("resources/world/Trees.png")));
	m_Tilesets.emplace(std::pair("Props",  std::make_unique<sf::Texture>("resources/world/Props.png")));
	m_Tilesets.emplace(std::pair("Roofs",  std::make_unique<sf::Texture>("resources/world/Roofs.png")));
	m_Tilesets.emplace(std::pair("Walls",  std::make_unique<sf::Texture>("resources/world/Walls.png")));
	
	m_Terrain.Load("resources/world/map.tmx", m_Tilesets);
}

auto Game::CheckForBounds(const sf::Vector2f& position) -> bool
{
    if (position.x <= config::leftBound || position.x >= config::rightBound) 
        return true;
    if (position.y <= config::topBound || position.y >= config::bottomBound) 
        return true;
    return false;
}

auto Game::Run() -> void
{
	sf::Clock clock;
    float timer = 0.0f;
	while (m_Window.isOpen())
	{
		while (const std::optional event = m_Window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				m_Window.close();
		}

		m_Window.clear();
		
		float dt = (clock.restart().asSeconds());
		m_Window.draw(m_Terrain);
		m_Camera.SetCenterPoint(m_Player.GetPos(), m_Window);
        
        // Uncomment following when trees are made as a entire object
        // std::sort(m_Entities.begin(), m_Entities.end(), [](Entity* a, Entity* b) { return a->GetPos().y < b->GetPos().y; });
        
        m_Window.draw(m_Player);
        m_Player.OnUpdate(dt);
        timer += dt;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && timer > config::shootingDelay)
        {
            auto mousePositon = m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window));
            auto proj = std::make_unique<Projectile>(m_Player.GetPos());
            proj->direction.x = mousePositon.x - m_Player.GetPos().x;
            proj->direction.y = mousePositon.y - m_Player.GetPos().y; 
            m_Projectiles.push_back(std::move(proj));
            timer = 0.0f;
        }

        for (const auto& projectile : m_Projectiles)
        {
            projectile->OnUpdate(dt);
            m_Window.draw(*projectile);
        }

        std::erase_if(m_Projectiles, [this](const auto& proj) { return CheckForBounds(proj->GetPos()); });
		
        m_Window.display();
	}
}



