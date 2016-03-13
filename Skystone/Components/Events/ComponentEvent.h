#ifndef COMPONENT_EVENT_H
#define COMPONENT_EVENT_H

class Scene;

class ComponentEvent
{
public:
	enum class Type {
		onDeath, 
		onCollision,
		onDamageTaken
	};

public:
	ComponentEvent(Type type, Scene& scene);
	virtual ~ComponentEvent();

	Scene& getScene() const;
	Type getType() const;

private:
	Type type_;
	Scene& scene_;
};

#endif //COMPONENT_EVENT_H