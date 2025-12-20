#include "animation.hpp"

Animation::Animation(const float frameDuration)
	:m_FrameDuration(frameDuration), m_LastFrameCount(0)
{
}

auto Animation::Update(const uint32_t frameCount) -> uint32_t
{
	if (frameCount != m_LastFrameCount)
	{
		m_CurrentFrame = 0;
		m_LastFrameCount = frameCount;
		m_Clock.restart();
	}

	if (m_Clock.getElapsedTime().asSeconds() > m_FrameDuration)
	{
		m_CurrentFrame = (m_CurrentFrame + 1) % frameCount;
		m_Clock.restart();
	}
	return m_CurrentFrame;
}
