#pragma once

#include "entity.hpp"
#include "animation.hpp"

#include <SFML/Graphics.hpp>

#include <memory>
#include <unordered_map>

enum class PlayerState { IdleDown, WalkUp, WalkDown, WalkRight, WalkLeft }; // TODO: Add idle animation in all directions

class Player : public Entity
{
public:
	Player();
	~Player() = default;

	auto OnUpdate(float dt) -> void override;
	auto GetPos() -> sf::Vector2f const override;

private:
	std::unordered_map<std::string, sf::Texture> m_Textures;
	std::unique_ptr<sf::Sprite> m_Sprite;
	std::unique_ptr<Animation> m_Animation;
	PlayerState m_CurrentState = PlayerState::IdleDown;
	bool m_FacingRight = false;
	const uint32_t m_TexStride = 64;
	const float m_Speed = 150.0f;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

