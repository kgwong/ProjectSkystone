#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "Components/Component.h"

class GameWindow;

class RenderComponent : public Component
{
public:
	RenderComponent(GameObject& owner);
	virtual ~RenderComponent() = 0;

	virtual void start(Level& level);
	virtual void update(Level& level);
	virtual void render(GameWindow& window, float percBehind) = 0;
	
	virtual Component::Type getType() final;

	virtual int getWidth();
	virtual int getHeight();

	virtual int getRenderLayer();

public: //protected
	Point getRenderPosition(float percBehind);

private:
	Point prevPosition;

};

#endif //RENDER_COMPONENT_H

