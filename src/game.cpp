#include "game.hpp"
#include "SFML/System/Vector2.hpp"
#include "enemy.hpp"
#include "global_config.hpp"
#include "projectile.hpp"

#include <memory>

Game::Game(const GameSpecification &spec) {
  m_Window.create(sf::VideoMode(sf::Vector2u(spec.width, spec.height)),
                  spec.title);
  m_Window.setVerticalSyncEnabled(true);

  m_Camera = std::make_unique<Camera>(m_Window);
  m_Window.setView(m_Camera->GetViewPoint());

  m_Tilesets.emplace(std::pair(
      "Water",
      std::make_unique<sf::Texture>("resources/world/Water_Tiles.png")));
  m_Tilesets.emplace(std::pair(
      "Floors_Tiles",
      std::make_unique<sf::Texture>("resources/world/Floors_Tiles.png")));
  m_Tilesets.emplace(std::pair(
      "Trees", std::make_unique<sf::Texture>("resources/world/Trees.png")));
  m_Tilesets.emplace(std::pair(
      "Props", std::make_unique<sf::Texture>("resources/world/Props.png")));
  m_Tilesets.emplace(std::pair(
      "Roofs", std::make_unique<sf::Texture>("resources/world/Roofs.png")));
  m_Tilesets.emplace(std::pair(
      "Walls", std::make_unique<sf::Texture>("resources/world/Walls.png")));
  m_Terrain.Load("resources/world/map.tmx", m_Tilesets);

  m_PlayerGUI = std::make_unique<PlayerGUI>(&m_Window);

  m_Entities.emplace_back(std::make_unique<Enemy>(&m_Player));
  m_Entities.emplace_back(std::make_unique<Enemy>(&m_Player));
  m_Entities.emplace_back(std::make_unique<Enemy>(&m_Player));
  m_Entities.emplace_back(std::make_unique<Enemy>(&m_Player));
  m_Entities.emplace_back(std::make_unique<Enemy>(&m_Player));
}

auto Game::CheckForBounds(const sf::Vector2f &position) -> bool const {
  if (position.x <= config::leftBound || position.x >= config::rightBound)
    return true;
  if (position.y <= config::topBound || position.y >= config::bottomBound)
    return true;
  return false;
}

auto Game::Run() -> void {
  sf::Clock clock;
  float timer = 0.0f;
  while (m_Window.isOpen()) {
    while (const std::optional event = m_Window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        m_Window.close();
    }

    m_Window.clear();

    float dt = (clock.restart().asSeconds());

    m_Window.setView(m_Camera->GetViewPoint());
    m_Camera->SetCenterPoint(m_Player.GetPos());

    m_Window.draw(m_Terrain);

    // Uncomment following when trees are made as a entire object
    // std::sort(m_Entities.begin(), m_Entities.end(), [](Entity* a, Entity* b)
    // { return a->GetPos().y < b->GetPos().y; });

    m_Window.draw(m_Player);
    m_Player.OnUpdate(dt);

    for (const auto& entity : m_Entities)
    {
        m_Window.draw(*entity);
        entity->OnUpdate(dt);
        m_Player.CheckForCollision(entity.get());
    }

    timer += dt;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
        timer > config::shootingDelay) {
      auto mousePositon =
          m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window));
      auto direction = sf::Vector2f(mousePositon.x - m_Player.GetPos().x,
                                    mousePositon.y - m_Player.GetPos().y);
      m_Projectiles.emplace_back(Projectile(m_Player.GetPos(), direction));
      timer = 0.0f;
    }

    for (auto &projectile : m_Projectiles) {
      projectile.OnUpdate(dt);
      m_Window.draw(projectile);
    }
    std::erase_if(m_Projectiles,
                  [this](auto &proj) { return CheckForBounds(proj.GetPos()); });

    m_Window.setView(m_Window.getDefaultView());

    m_PlayerGUI->Render();
    m_PlayerGUI->Update(m_Player.GetHealthPoints());

    m_Window.display();
  }
}
