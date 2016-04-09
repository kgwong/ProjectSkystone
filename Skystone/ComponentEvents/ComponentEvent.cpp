#include "ComponentEvent.h"

#include "Components/Component.h"

ComponentEvent::ComponentEvent(Scene& scene)
	:scene_(scene)
{
}

ComponentEvent::~ComponentEvent()
{
}

void ComponentEvent::dispatch(ComponentEventReceiver& eventReceiver) const
{
	eventReceiver.handleEvent(*this);
}

Scene& ComponentEvent::getScene() const
{
	return scene_;
}
