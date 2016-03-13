#include "ComponentEvent.h"



ComponentEvent::ComponentEvent(Type type, Scene& scene)
	:type_(type), scene_(scene)
{
}

ComponentEvent::~ComponentEvent()
{
}

Scene& ComponentEvent::getScene() const
{
	return scene_;
}

ComponentEvent::Type ComponentEvent::getType() const
{
	return type_;
}
