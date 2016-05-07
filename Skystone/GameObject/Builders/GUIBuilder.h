#ifndef GUI_BUILDER_H
#define GUI_BUILDER_H

class GameObject;
class ComponentSystem;

#include <string>
#include <memory>

class GUIBuilder
{
public:
	GUIBuilder();
	~GUIBuilder();

	std::shared_ptr<GameObject> build(ComponentSystem& componentSystem, const std::string& name, GameObject* player);

private:
	std::shared_ptr<GameObject> textSelector_;
};

#endif // GUI_BUILDER_H
