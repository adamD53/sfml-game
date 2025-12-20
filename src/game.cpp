#include "game.hpp"
#include "player.hpp"

Game::Game(const GameSpecification& spec)
{
	m_Window.create(sf::VideoMode(sf::Vector2u(spec.width, spec.height)), spec.title);

	m_Camera.SetViewPoint(m_Window);

	m_Player = std::make_unique<Player>();

	m_Tilesets.emplace(std::pair("Water", new sf::Texture("resources/world/Water_Tiles.png")));
	m_Tilesets.emplace(std::pair("Floors_Tiles", new sf::Texture("resources/world/Floors_Tiles.png")));
	m_Tilesets.emplace(std::pair("Trees", new sf::Texture("resources/world/Trees.png")));
	m_Tilesets.emplace(std::pair("Props", new sf::Texture("resources/world/Props.png")));
	m_Tilesets.emplace(std::pair("Roofs", new sf::Texture("resources/world/Roofs.png")));
	m_Tilesets.emplace(std::pair("Walls", new sf::Texture("resources/world/Walls.png")));
	
	m_Terrain.Load("resources/world/map.tmx", m_Tilesets);
    m_Entities = m_Terrain.GetStaticEntities();
    m_Entities.push_back(m_Player.get());
}

Game::~Game()
{
	for (const auto& t : m_Tilesets)
		delete t.second;
    
    for (const auto& e : m_StaticEntities)
        delete e;
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
		
		float dt = (clock.restart().asSeconds());
		m_Window.draw(m_Terrain);
		m_Camera.SetCenterPoint(m_Player->GetPos(), m_Window);
       
        for (const auto& entity : m_Entities)
            m_Window.draw(*entity);
		
        m_Player->OnUpdate(dt);
		
        m_Window.display();
	}
}



