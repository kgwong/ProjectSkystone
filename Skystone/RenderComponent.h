#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "Component.h"

class RenderComponent : public Component
{
public:
	RenderComponent(GameObject& owner);
	virtual ~RenderComponent() = 0;

	virtual Component::Type getType() final;

	int x() { 
		std::cout << "this is actually getting used" << std::endl;
		return owner_.getPosX(); 
	}
	int y() { 
		std::cout << "this is actualyl getting used" << std::endl;
		return owner_.getPosY(); 
	}

	virtual int getWidth();
	virtual int getHeight();

	virtual int getRenderLayer();
};

#endif //RENDER_COMPONENT_H

