#ifndef COMPONENT_EVENT_H
#define COMPONENT_EVENT_H

class Scene;
class ComponentEventReceiver;

class ComponentEvent
{
public:
	ComponentEvent(Scene& scene);
	virtual ~ComponentEvent();

	virtual void dispatch(ComponentEventReceiver& eventReceiver) const;

	Scene& getScene() const;

private:
	Scene& scene_;
};

#endif //COMPONENT_EVENT_H