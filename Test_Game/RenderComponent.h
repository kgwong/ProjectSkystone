#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "Component.h"

class RenderComponent : public Component
{
public:
	RenderComponent();
	virtual ~RenderComponent();

	virtual void update(GameObject& owner);
};

#endif //RENDER_COMPONENT_H

