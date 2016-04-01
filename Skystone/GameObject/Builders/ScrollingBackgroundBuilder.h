#ifndef SCROLLING_BACKGROUND_BUILDER_H
#define SCROLLING_BACKGROUND_BUILDER_H

#include <string>
#include <memory>

class GameObject;
class ComponentSystem;

class ScrollingBackgroundBuilder
{
public:
	ScrollingBackgroundBuilder();
	~ScrollingBackgroundBuilder();

	std::shared_ptr<GameObject> build(ComponentSystem& componentSystem, const std::string& backgroundName);
};

#endif // SCROLLING_BACKGROUND_BUILDER_H
