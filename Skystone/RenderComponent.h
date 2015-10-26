#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "Component.h"


#include "GameWindow.h"

//change to virtual class

class RenderComponent : public Component
{
public:
	RenderComponent() {};
	virtual ~RenderComponent() {} ;

	virtual void start(GameObject& owner) {};
	virtual void update(GameObject& owner) {} ;

	virtual int getWidth() { return 0; }
	virtual int getHeight() { return 0; }
};

#endif //RENDER_COMPONENT_H

