#ifndef COMPONENT_EVENT_RECEIVER_H
#define COMPONENT_EVENT_RECEIVER_H

//add include
#include "ComponentEvent.h"
#include "CollisionEvent.h"
#include "DamageTakenEvent.h"
#include "OnDeathEvent.h"

class ComponentEventReceiver
{
public:
	virtual void handleEvent(const ComponentEvent& e) {} 
	virtual void handleEvent(const CollisionEvent& e) {} 
	virtual void handleEvent(const DamageTakenEvent& e) {} 
	virtual void handleEvent(const OnDeathEvent& e) {} 
	//add overload for each event deriving from ComponentEvent
};

#endif //COMPONENT_EVENT_RECEIVER_H