#include "ComponentEvent.h"



ComponentEvent::ComponentEvent(Type type, Level& level)
	:type_(type), level_(level)
{
}

ComponentEvent::~ComponentEvent()
{
}

Level& ComponentEvent::getLevel() const
{
	return level_;
}

ComponentEvent::Type ComponentEvent::getType() const
{
	return type_;
}
