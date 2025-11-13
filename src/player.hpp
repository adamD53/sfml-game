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
	auto OnDraw(sf::RenderWindow& window) -> void override;
	auto GetPos() -> sf::Vector2f const override;

private:
	std::unordered_map<std::string, sf::Texture> m_Textures;
	std::unique_ptr<sf::Sprite> m_Sprite;
	std::unique_ptr<Animation> m_Animation;
	PlayerState m_CurrentState = PlayerState::IdleDown;
	bool m_FacingRight = false;
	
	int m_TexStride = 64;
};

