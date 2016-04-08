#include "OnDeathEvent.h"

#include "ComponentEventReceiver.h"

OnDeathEvent::OnDeathEvent(Scene& scene)
	:ComponentEvent(scene)
{
}


OnDeathEvent::~OnDeathEvent()
{
}

void OnDeathEvent::dispatch(ComponentEventReceiver& eventReceiver) const
{
	eventReceiver.handleEvent(*this);
}
