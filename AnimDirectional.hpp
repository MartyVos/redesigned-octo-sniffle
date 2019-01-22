#ifndef ANIMATION_DIRECTIONAL_HPP
#define ANIMATION_DIRECTIONAL_HPP

#include "AnimBase.hpp"

class AnimDirectional : public AnimBase {
protected:
	void FrameStep();
	void CropSprite();
};

#endif // ANIMATION_DIRECTIONAL_HPP