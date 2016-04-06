#ifndef ON_DEATH_EVENT_H
#define ON_DEATH_EVENT_H

#include "ComponentEvent.h"

class OnDeathEvent : public ComponentEvent
{
public:
	OnDeathEvent(Scene& scene);
	virtual ~OnDeathEvent();

	virtual void dispatch(ComponentEventReceiver& eventReceiver) const;
};

#endif //ON_DEATH_EVENT_H