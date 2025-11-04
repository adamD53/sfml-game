#include "game.h"
#include "player.h"

#include <iostream>

Game::Game(const GameSpecification& spec)
{
	m_Window.create(sf::VideoMode(sf::Vector2u(spec.width, spec.height)), spec.title);

	m_Camera.SetViewPoint(m_Window);

	m_Player = new Player;

	m_Tilesets.emplace_back(new sf::Texture("resources/world/Water_Tiles.png"));
	m_Tilesets.emplace_back(new sf::Texture("resources/world/Floors_Tiles.png"));
	m_Tilesets.emplace_back(new sf::Texture("resources/world/Trees.png"));
	m_Tilesets.emplace_back(new sf::Texture("resources/world/Props.png"));
	m_Tilesets.emplace_back(new sf::Texture("resources/world/Roofs.png"));
	m_Tilesets.emplace_back(new sf::Texture("resources/world/Walls.png"));
	
	m_World.Load("resources/world/map.tmx", m_Tilesets);

	m_Entities.emplace_back(m_Player);
}

Game::~Game()
{
	for (const auto& e : m_Entities)
		delete e;

	for (const auto& t : m_Tilesets)
		delete t;
}

auto Game::Run() -> void
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

		m_Window.display();
	}
}
