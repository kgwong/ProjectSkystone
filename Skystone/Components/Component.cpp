#include "Component.h"

Component::Component(GameObject& owner)
	:owner_(owner)
{

}

Component::~Component()
{
}

void Component::start(Scene& scene)
{
}

void Component::update(Scene& scene)
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

void Component::setOwned(bool owned)
{
	owned_ = owned;
}
