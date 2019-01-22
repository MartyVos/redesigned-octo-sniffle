#include "AnimDirectional.hpp"
#include "SpriteSheet.hpp"

void AnimDirectional::CropSprite() {
	sf::IntRect rect(
		m_spriteSheet->GetSpriteSize().x * m_frameCurrent,
		m_spriteSheet->GetSpriteSize().y *
		(m_frameRow + (short)m_spriteSheet->GetDirection()),
		m_spriteSheet->GetSpriteSize().x,
		m_spriteSheet->GetSpriteSize().y);
	m_spriteSheet->CropSprite(rect);
}

void AnimDirectional::FrameStep() {
	if (m_frameTime == 0.0) { return; }
	if (m_frameStart < m_frameEnd) { ++m_frameCurrent; }
	else { --m_frameCurrent; }

	if ((m_frameStart < m_frameEnd && m_frameCurrent > m_frameEnd) ||
		(m_frameStart > m_frameEnd && m_frameCurrent < m_frameEnd))
	{
		if (m_loop) { m_frameCurrent = m_frameStart; return; }
		m_frameCurrent = m_frameEnd;
		Pause();
	}
}
