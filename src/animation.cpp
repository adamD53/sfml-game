#include "animation.hpp"

Animation::Animation(const float frameDuration)
	:m_FrameDuration(frameDuration), m_LastFrameCount(0)
{
}

auto Animation::Update(const uint32_t frames) -> uint32_t
{
	if (frames != m_LastFrameCount)
	{
		m_CurrentFrame = 0;
		m_LastFrameCount = frames;
		m_Clock.restart();
	}

	if (m_Clock.getElapsedTime().asSeconds() > m_FrameDuration)
	{
		m_CurrentFrame = (m_CurrentFrame + 1) % frames;
		m_Clock.restart();
	}
	return m_CurrentFrame;
}
