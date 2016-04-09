#include "Component.h"

Component::Component(GameObject& owner)
	:owner_(owner)
{

}

Component::~Component()
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
