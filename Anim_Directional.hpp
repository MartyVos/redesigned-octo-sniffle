#ifndef ANIMATION_DIRECTIONAL_HPP
#define ANIMATION_DIRECTIONAL_HPP

#include "Anim_Base.hpp"

class Anim_Directional : public Anim_Base {
protected:
	void FrameStep();
	void CropSprite();
};

#endif // ANIMATION_DIRECTIONAL_HPP