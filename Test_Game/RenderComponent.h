#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include "GameWindow.h"

#include "GameObject.h"
#include "Animation.h"

class RenderComponent
{
public:
	RenderComponent(GameWindow* gameWindow);
	virtual ~RenderComponent();

	void setAnimation(Animation* animation);

	virtual void update(GameObject& owner);
	

private:
	GameWindow* _window;
	Animation* _animation;
};

#endif //RENDERCOMPONENT_H
