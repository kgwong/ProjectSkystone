#ifndef DAMAGE_TAKEN_EVENT_H
#define DAMAGE_TAKEN_EVENT_H

#include "ComponentEvent.h"

class DamageTakenEvent : public ComponentEvent
{
public:
	DamageTakenEvent(Scene& scene);
	virtual ~DamageTakenEvent();

	virtual void dispatch(ComponentEventReceiver& eventReceiver) const;
};

#endif //DAMAGE_TAKEN_EVENT_H