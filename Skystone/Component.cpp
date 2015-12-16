#include "Component.h"

Component::Component(GameObject& owner)
	:owner_(owner)
{

}

Component::~Component()
{
}

void Component::start(Level& level)
{
}

void Component::update(Level& level)
{
}

void Component::handleEvent(const CollisionEvent& e)
{
}

void Component::handleEvent(const ComponentEvent& e)
{
}

Component::Type Component::getType()
{
	return Component::Type::UNKNOWN;
}

bool Component::owned()
{
	return owned_;
}

void Component::disown()
{
	owned_ = false;
}
