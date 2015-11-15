#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "Component.h"

class RenderComponent : public Component
{
public:
	virtual ~RenderComponent() {};

	virtual void start(GameObject& owner, Level& level) = 0;
	virtual void update(GameObject& owner, Level& level) = 0;

	virtual int getWidth() { return 0; }
	virtual int getHeight() { return 0; }
};

#endif //RENDER_COMPONENT_H

