#include "DamageTakenEvent.h"

#include "ComponentEventReceiver.h"

DamageTakenEvent::DamageTakenEvent(Scene& scene)
	:ComponentEvent(scene)
{
}


DamageTakenEvent::~DamageTakenEvent()
{
}

void DamageTakenEvent::dispatch(ComponentEventReceiver& eventReceiver) const
{
	eventReceiver.handleEvent(*this);
}
