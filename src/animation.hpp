#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(const float frameDuration);
	~Animation() = default;

	auto Update(const uint32_t frameCount) -> uint32_t;

private:
	sf::Clock m_Clock;
	uint32_t m_CurrentFrame = 0;
	const float m_FrameDuration;
	uint32_t m_LastFrameCount;
};

