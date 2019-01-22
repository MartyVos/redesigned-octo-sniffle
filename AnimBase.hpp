#ifndef ANIMATION_BASE_HPP
#define ANIMATION_BASE_HPP

#include <iostream>

class SpriteSheet;
using Frame = unsigned int;

class AnimBase {
	friend class SpriteSheet;
public:
	AnimBase();
	virtual ~AnimBase();

	void Play();
	void Pause();
	void Stop();
	void Reset();

	virtual void Update(const float &l_dT);
	void SetSpriteSheet(SpriteSheet* l_sheet);
	void SetFrame(const unsigned int &l_frame);
	void SetLooping(const bool &l_loop);
	void SetName(const std::string &l_name);
	bool IsInAction();

protected:
	virtual void FrameStep() = 0;
	virtual void CropSprite() = 0;

	Frame m_frameCurrent;
	Frame m_frameStart;
	Frame m_frameEnd;
	Frame m_frameRow;
	Frame m_frameActionStart;		//Frame when a specific "action" begins
	Frame m_frameActionEnd;		//Frame when a specific "action" end
	float m_frameTime;
	float m_elapsedTime;
	bool m_loop;
	bool m_playing;
	std::string m_name;
	SpriteSheet* m_spriteSheet;
};

#endif // ANIMATION_BASE_HPP