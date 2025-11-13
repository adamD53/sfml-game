#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
public:
	Animation(const float frameDuration);
	~Animation() = default;

	auto Update(const uint32_t frames) -> int;

private:
	sf::Clock m_Clock;
	int m_CurrentFrame = 0;
	const float m_FrameDuration;
	int m_LastFrameCount;
};

