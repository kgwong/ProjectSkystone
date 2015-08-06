#ifndef ANIMATION_RENDERER_H
#define ANIMATION_RENDERER_H

#include "GameWindow.h"
#include "GameObject.h"
#include "Animation.h"
#include "RenderComponent.h"

class AnimationRenderer : public RenderComponent
{
public:
	AnimationRenderer(Animation* animation);
	virtual ~AnimationRenderer();

	virtual void update(GameObject& owner);
	

private:
	Animation* _animation;
	int _currFrame;

private:
	void incrementFrame();
};

#endif //RENDERCOMPONENT_H
