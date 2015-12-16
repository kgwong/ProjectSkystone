#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "Component.h"

class RenderComponent : public Component
{
public:
	RenderComponent(GameObject& owner);
	virtual ~RenderComponent() = 0;

	virtual Component::Type getType() final;

	virtual int getWidth();
	virtual int getHeight();

	virtual int getRenderLayer();
};

#endif //RENDER_COMPONENT_H

