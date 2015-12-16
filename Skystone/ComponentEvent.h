#ifndef COMPONENT_EVENT_H
#define COMPONENT_EVENT_H

class Level;

class ComponentEvent
{
public:
	enum class Type {
		onDeath, onCollision
	};

public:
	ComponentEvent(Type type, Level& level);
	virtual ~ComponentEvent();

	Level& getLevel() const;
	Type getType() const;

private:
	Type type_;
	Level& level_;
};

#endif //COMPONENT_EVENT_H