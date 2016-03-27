#ifndef BACKGROUND_BUILDER_H
#define BACKGROUND_BUILDER_H

#include <string>
#include <memory>

class GameObject;
class ComponentSystem;

class BackgroundBuilder
{
public:
	BackgroundBuilder();
	~BackgroundBuilder();

	std::shared_ptr<GameObject> build(ComponentSystem& componentSystem, const std::string& backgroundName);
};

#endif // BACKGROUND_BUILDER_H
