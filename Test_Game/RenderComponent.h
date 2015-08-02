#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "GameWindow.h"

#include "GameObject.h"
#include "Animation.h"

class RenderComponent
{
public:
	RenderComponent(Animation* animation);
	virtual ~RenderComponent();

	virtual void update(GameObject& owner);
	

private:
	Animation* _animation;
	int _currFrame;

private:
	void incrementFrame();
};

#endif //RENDERCOMPONENT_H
