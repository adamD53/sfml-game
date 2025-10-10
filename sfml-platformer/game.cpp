#include "game.h"
#include "player.h"

#include <iostream>

Game::Game(const GameSpecification& spec)
{
	m_Window.create(sf::VideoMode(sf::Vector2u(spec.width, spec.height)), spec.title);

	m_Camera.SetViewPoint(m_Window);

	m_Player = new Player;

	m_Tilesets.emplace_back(new sf::Texture("res/world/Water_Tiles.png"));
	m_Tilesets.emplace_back(new sf::Texture("res/world/Floors_Tiles.png"));
	m_Tilesets.emplace_back(new sf::Texture("res/world/Props.png"));
	m_Tilesets.emplace_back(new sf::Texture("res/world/Roofs.png"));
	m_Tilesets.emplace_back(new sf::Texture("res/world/Trees.png"));
	m_Tilesets.emplace_back(new sf::Texture("res/world/Walls.png"));
	
	if (!m_World.OnLoad("res/world/map.tmx", m_Tilesets))
		std::cerr << "Failed to load worldmap" << std::endl;

	m_Entities.emplace_back(m_Player);
}

Game::~Game()
{
	for (const auto& e : m_Entities)
		delete e;

	for (const auto& t : m_Tilesets)
		delete t;
}

void Game::Run()
{
	sf::Clock clock;
	while (m_Window.isOpen())
	{
		while (const std::optional event = m_Window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				m_Window.close();
		}

		m_Window.clear();

		m_Window.draw(m_World);
		m_Camera.SetCenterPoint(m_Player->GetPos(), m_Window);

		float dt = (clock.restart().asSeconds());
		for (const auto& e : m_Entities)
		{
			e->OnDraw(m_Window);
			e->OnUpdate(dt);
		}

		// Update the window
		m_Window.display();
	}
}
