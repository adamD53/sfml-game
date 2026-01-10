#include "player.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "global_config.hpp"

Player::Player()
    : m_HealthPoints(100.f)
{
    m_AnimationTextures.emplace(std::make_pair("walk_down", sf::Texture("resources/player/Walk_Down-Sheet.png")));
    m_AnimationTextures.emplace(std::make_pair("walk_up", sf::Texture("resources/player/Walk_Up-Sheet.png")));
    m_AnimationTextures.emplace(std::make_pair("walk_side", sf::Texture("resources/player/Walk_Side-Sheet.png")));
    m_AnimationTextures.emplace(std::make_pair("idle_down", sf::Texture("resources/player/Idle_Down-Sheet.png")));

    m_Sprite = std::make_unique<sf::Sprite>(m_AnimationTextures["idle_down"]);
    auto [width, height] = m_Sprite->getTextureRect().size;
    m_Sprite->setTextureRect(sf::IntRect({16, 16}, {32, 32}));
    m_Sprite->setOrigin({16 / 2.f, height / 2.f});
    m_Sprite->setPosition(config::playerInitialPosition);

    m_Animation = std::make_unique<Animation>(0.2f);
}

auto Player::GetBounds() -> sf::FloatRect const
{
    return m_Sprite->getGlobalBounds();
}

auto Player::GetPos() -> sf::Vector2f const
{
    return m_Sprite->getPosition();
}

auto Player::GetHealthPoints() -> float&
{
    return m_HealthPoints;
}

auto Player::CheckForCollision(Entity* target) -> bool const
{
    if (Player::GetBounds().findIntersection(target->GetBounds()))
    {
        return true;
    }
    return false;
}

auto Player::OnUpdate(float dt) -> void
{
    sf::Vector2f direction(0.0f, 0.0f);
    uint32_t currentAnimationFrameIndex = 0;
    int animationRow = 0;

    m_CurrentState = PlayerState::IdleDown;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && (Player::GetPos().x > config::leftBound))
    {
        direction.x += -1.0f;
        m_CurrentState = PlayerState::WalkLeft;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && (Player::GetPos().x < config::rightBound))
    {
        direction.x += 1.0f;
        m_CurrentState = PlayerState::WalkRight;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && (Player::GetPos().y > config::topBound))
    {
        direction.y += -1.0f;
        m_CurrentState = PlayerState::WalkUp;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && (Player::GetPos().y < config::bottomBound))
    {
        direction.y += 1.0f;
        m_CurrentState = PlayerState::WalkDown;
    }

    const uint32_t framesCount = (m_CurrentState == PlayerState::IdleDown) ? 4 : 6;
    currentAnimationFrameIndex = m_Animation->Update(framesCount);
    switch (m_CurrentState)
    {
        case PlayerState::IdleDown:
            m_Sprite->setTexture(m_AnimationTextures["idle_down"]);
            animationRow = 16;
            break;
        case PlayerState::WalkUp:
            m_Sprite->setTexture(m_AnimationTextures["walk_up"]);
            animationRow = 16;
            break;
        case PlayerState::WalkDown:
            m_Sprite->setTexture(m_AnimationTextures["walk_down"]);
            animationRow = 16;
            break;
        case PlayerState::WalkRight:
            m_FacingRight = true;
            m_Sprite->setTexture(m_AnimationTextures["walk_side"]);
            animationRow = 16;
            break;
        case PlayerState::WalkLeft:
            m_FacingRight = false;
            m_Sprite->setTexture(m_AnimationTextures["walk_side"]);
            animationRow = 16;
            break;
    }

    int frameX = currentAnimationFrameIndex * m_TexStride;
    m_Sprite->setTextureRect(
        sf::IntRect({frameX, animationRow}, {config::playerTextureWidth, config::playerTextureHeight}));

    m_Sprite->move((direction.length() <= 1 ? direction : direction.normalized()) * m_Speed * dt);
    m_Sprite->setScale({(m_FacingRight ? 1.0f : -1.0f), 1.0f});
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*m_Sprite, states);
}
