#include "ComponentSubsystem.h"

#include "Components/Component.h"
#include "Util/vector_util.h"

ComponentSubsystem::ComponentSubsystem()
{
}


ComponentSubsystem::~ComponentSubsystem()
{
}

void ComponentSubsystem::addComponent(std::shared_ptr<Component> component)
{
	components_.push_back(component);
}

void ComponentSubsystem::update(Scene& scene)
{
	typedef std::shared_ptr<Component> comp;
	util::vector::update_or_remove(components_,
									[](comp& c) { return !c->owned(); },
									[&scene](comp& c) { return c->update(scene);}
	);
}

void ComponentSubsystem::cleanup()
{
	typedef std::shared_ptr<Component> comp;
	util::vector::update_or_remove(components_,
		[](comp& c) { return !c->owned(); },
		[](comp& c) {}
	);
}
